using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Text.Json;
using System.Windows.Input;
using Editor.Core;
using Editor.Models;
using Editor.Views;

namespace Editor.ViewModels
{
    public class ProjectSelectionViewModel : ViewModelBase
    {
        public static ObservableCollection<ProjectRecent> recentProjects { get; set; }
        private static readonly string __recentProjectFile = "recent_projects.json";

        private ProjectRecent? __selectedRecentProject;
        private ProjectMetadata? __selectedProject;

        public ProjectMetadata? selectedProject
        {
            get { return __selectedProject; }
            set
            {
                if (__selectedProject != value)
                {
                    __selectedProject = value;
                    OnPropertyChanged();
                }
            }
        }

        public ProjectRecent? selectedRecentProject
        {
            get { return __selectedRecentProject; }
            set
            {
                if (__selectedRecentProject != value)
                {
                    __selectedRecentProject = value;
                    OnPropertyChanged();
                    selectedProject = ProjectContext.LoadProjectMetadata(
                        __selectedRecentProject.Path
                    );
                }
            }
        }

        public ICommand RemoveProjectCommand { get; }
        public ICommand AddNewProjectCommand { get; }
        public ICommand OpenSelectedCommand { get; }

        public ProjectSelectionViewModel()
        {
            recentProjects = new ObservableCollection<ProjectRecent>();
            RemoveProjectCommand = new RelayCommand(RemoveProject);
            AddNewProjectCommand = new RelayCommand(AddNewProject);
            OpenSelectedCommand = new RelayCommand(
                execute: () =>
                {
                    OpenSelectedProject();
                },
                canExecute: CanOpenSelectedProject
            );
            LoadRecentProjects();
            //AddRecentProjects("FirstProject", "some path you know");
            //AddRecentProjects("SecondProject", "some path you know");
        }

        public bool OpenSelectedProject()
        {
            if (selectedProject != null)
            {
                ProjectContext.SetupCurrentContext(selectedProject.Base);
                VoxleEditorView editorView = new VoxleEditorView();
                editorView.Show();
                return true;
            }
            return false;
        }

        private bool CanOpenSelectedProject()
        {
            return !String.IsNullOrEmpty(selectedProject?.Base);
        }

        public void LoadRecentProjects()
        {
            if (!File.Exists(__recentProjectFile))
                return;

            try
            {
                string jsonString = File.ReadAllText(__recentProjectFile);
                var loadedData = JsonSerializer.Deserialize<List<ProjectRecent>>(jsonString);

                if (loadedData != null)
                {
                    recentProjects.Clear();
                    foreach (var project in loadedData)
                    {
                        if (Directory.Exists(project.Path))
                        {
                            recentProjects.Add(project);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void AddRecentProjects(string name, string path)
        {
            ProjectRecent recentModel = new ProjectRecent();
            recentModel.Name = name;
            recentModel.Path = path;
            if (recentProjects.Contains(recentModel))
            {
                recentProjects.Remove(recentModel);
            }
            recentProjects.Insert(0, recentModel);
            SaveRecentProjects();
        }

        public static void SaveRecentProjects()
        {
            try
            {
                var options = new JsonSerializerOptions { WriteIndented = true };
                string jsonString = JsonSerializer.Serialize(recentProjects, options);
                File.WriteAllText(__recentProjectFile, jsonString);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error saving recent projects: {ex.Message}");
            }
        }

        private void RemoveProject(object? parameter)
        {
            if (parameter is ProjectRecent projectToRemove)
            {
                if (projectToRemove != null && recentProjects.Contains(projectToRemove))
                {
                    recentProjects.Remove(projectToRemove);
                    SaveRecentProjects();
                }
            }
        }

        private void AddNewProject(object? parameter)
        {
            if (parameter is ProjectMetadata projectMetadata)
            {
                AddRecentProjects(projectMetadata.Name, projectMetadata.Base);
            }
        }
    }
}
