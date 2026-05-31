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
