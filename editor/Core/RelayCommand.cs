using System;
using System.Windows.Input;

namespace Editor.Core
{
    public sealed class RelayCommand : ICommand
    {
        private readonly Action<object?> _execute;
        private readonly Func<object?, bool>? _canExecute;
