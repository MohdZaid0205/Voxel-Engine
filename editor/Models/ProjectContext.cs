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
            {
                Directory.CreateDirectory(projectMetadata.Base);
                ProjectTemplate template = new ProjectTemplate(projectMetadata);
            }
            StoreProjectMetadata(projectMetadata);
            currentContext = projectMetadata;
        }

        public static ProjectMetadata LoadProjectMetadata(string path)
        {
            string metadata_file = Path.Combine(path, "metadata.json");
            using FileStream fileStream = File.OpenRead(metadata_file);
            return JsonSerializer.Deserialize<ProjectMetadata>(fileStream);
        }

        public static void StoreProjectMetadata(ProjectMetadata projectMetadata)
        {
            var options = new JsonSerializerOptions { WriteIndented = true };
            string metadata_file = Path.Combine(projectMetadata.Base, "metadata.json");
            using FileStream fileStream = File.Create(metadata_file);
            JsonSerializer.Serialize(fileStream, projectMetadata, options);
        }

        public static void SetupCurrentContext(string path)
        {
            if (currentContext != null)
            {
                DestroyCurrentContext();
            }
            currentContext = LoadProjectMetadata(path);
        }

        public static void DestroyCurrentContext()
        {
            StoreProjectMetadata(currentContext);
            currentContext = null;
        }
    }
}
