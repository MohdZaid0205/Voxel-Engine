using Editor.Core;
using Editor.Models;
using System;
using System.Windows.Input;

namespace Editor.ViewModels
{

	public class CreateProjectViewModel : ViewModelBase
	{
		public ProjectMetadata newProject { get; set; }

		public ICommand CreateCommand { get; set; }

		public CreateProjectViewModel()
		{
			newProject = new ProjectMetadata();
			CreateCommand = new RelayCommand(execute: Create, canExecute: CanCreate);
		}

		public string Name
		{
			get { return newProject.Name; }
			set
			{
				newProject.Name = value;
				OnPropertyChanged();
			}
		}

		public string Path
		{
			get { return newProject.Base; }
			set
			{
				newProject.Base = value;
				OnPropertyChanged();
			}
		}

		public string Author
		{
			get { return newProject.Author; }
			set
			{
				newProject.Author = value;
				OnPropertyChanged();
			}
		}

		public string Desciption
		{
			get { return newProject.Description; }
			set
			{
				newProject.Description = value;
				OnPropertyChanged();
			}
		}

		public string License
		{
			get { return newProject.License; }
			set
			{
				newProject.License = value;
				OnPropertyChanged();
			}
		}

		public DateTime CreatedAt
		{
			get { return newProject.CreatedAt; }
			set
			{
				newProject.CreatedAt = value;
				OnPropertyChanged();
			}
		}

		public DateTime UpdatedAt
		{
			get { return newProject.UpdatedAt; }
			set
			{
				newProject.UpdatedAt = value;
				OnPropertyChanged();
			}
		}

		private void Create()
		{
			if (newProject != null)
			{
				CreatedAt = DateTime.Now;
				UpdatedAt = DateTime.Now;
				ProjectContext.CreateProject(newProject);
				ProjectSelectionViewModel.AddRecentProjects(newProject.Name, newProject.Base);
			}
		}

		private bool CanCreate()
		{
			return !String.IsNullOrEmpty(newProject.Name) && !String.IsNullOrEmpty(Path);
		}
	}
}
