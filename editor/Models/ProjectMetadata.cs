using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace Editor.Models
{
    public class ProjectMetadata
    {
        public string Name { get; set; }
        public string Base { get; set; }

        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string? Author { get; set; }

        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string? License { get; set; }

        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        public string? Description { get; set; }

        public HashSet<string> IncludedFiles { get; set; }
        public HashSet<string> ExcludedFiles { get; set; }
        public DateTime CreatedAt { get; set; }
        public DateTime UpdatedAt { get; set; }
    }
}
