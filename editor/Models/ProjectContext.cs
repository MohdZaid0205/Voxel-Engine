using System.IO;
using System.Text.Json;

namespace Editor.Models
{
    public class ProjectContext
    {
        // information regarding current context (serializable)
        public static ProjectMetadata? currentContext { get; set; }

        public static void CreateProject(ProjectMetadata projectMetadata)
        {
            currentContext = projectMetadata;
            if (!Directory.Exists(projectMetadata.Base))
