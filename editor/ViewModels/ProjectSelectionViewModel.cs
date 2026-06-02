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
