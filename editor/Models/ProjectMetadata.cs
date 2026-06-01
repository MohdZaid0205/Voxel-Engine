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

