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
