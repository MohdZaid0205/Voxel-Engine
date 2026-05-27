#pragma region Engine::Attempt Implementation

template<typename Func, typename ...Args>
inline Engine::Attempt::Runner<Func, Args...>::Runner(Func&& func, Args&&... args)
	: _func(std::forward<Func>(func)), _args(std::forward<Args>(args)...) {}

template<typename Func, typename ...Args>
inline Engine::Attempt::Runner<Func, Args...>&
Engine::Attempt::Runner<Func, Args...>::prepare(Hook func) {
	_prep = std::move(func);
	return *this;
}

template<typename Func, typename ...Args>
inline Engine::Attempt::Runner<Func, Args...>&
Engine::Attempt::Runner<Func, Args...>::restore(Hook func) {
	_rest = std::move(func);
	return *this;
}

template<typename Func, typename ...Args>
inline Engine::Attempt::Runner<Func, Args...>&
Engine::Attempt::Runner<Func, Args...>::complete(Hook func) {
	_comp = std::move(func);
	return *this;
}


template<typename Func, typename ...Args>
template<typename ...FArgs>
inline Engine::Attempt::Runner<Func, Args...>&
Engine::Attempt::Runner<Func, Args...>::does(FArgs&& ...args) noexcept {
	_does_log = [...args = std::forward<FArgs>(args)]() mutable {
		Engine::Console::Info("[A] =>"_D, args...);
		};
	return *this;
}

template<typename Func, typename ...Args>
template<typename ...FArgs>
inline Engine::Attempt::Runner<Func, Args...>&
Engine::Attempt::Runner<Func, Args...>::pass(FArgs&& ...args) noexcept {
	_pass_log = [...args = std::forward<FArgs>(args)]() mutable {
		Engine::Console::Info("[A] P>"_D, args...);
		};
	return *this;
}

template<typename Func, typename ...Args>
template<typename ...FArgs>
inline Engine::Attempt::Runner<Func, Args...>&
Engine::Attempt::Runner<Func, Args...>::warn(FArgs&& ...args) noexcept {
	_warn_log = [...args = std::forward<FArgs>(args)]() mutable {
		Engine::Console::Warn("[A] W>"_D, args...);
		};
	return *this;
}

template<typename Func, typename ...Args>
template<typename ...FArgs>
inline Engine::Attempt::Runner<Func, Args...>&
Engine::Attempt::Runner<Func, Args...>::fail(FArgs&& ...args) noexcept {
	_fail_log = [...args = std::forward<FArgs>(args)]() mutable {
		Engine::Console::Error("[A] F>"_D, args...);
		};
	return *this;
}

template<typename Func, typename ...Args>
inline std::invoke_result_t<Func, Args...> 
Engine::Attempt::Runner<Func, Args...>::execute(const String& context) {

	_does_log();

	if (!_prep(context)) {
		Engine::Console::Error("[A] ->"_D, "PreparationPhaseFailed"_B);
		Engine::Console::Error("[A] ->"_D, "Transaction aborted before execution as PreperationPhaseFailed"_D);
		_fail_log();

		return std::unexpected(Engine::Attempt::makeError("PreparationPhaseFailed", "The preparation hook returned false."));
	}


	_result = std::apply(_func, std::move(_args));
	_eval = true;

	if (_result.has_value()) {
		if (!_comp(context)) {
			Engine::Console::Error("[A] ->"_D, "CompletionHookFailed"_B);
			Engine::Console::Error("[A] ->"_D, "Main task succeeded, cleanup failed as CompletionHookFailed"_D);
			_fail_log();

			return std::unexpected(Engine::Attempt::makeError("CompletionHookFailed", "The completion hook returned false."));
		}
		_pass_log();
	}
	else {
		const auto& err = _result.error();

		if (err.type == Status::Warning || err.type == Status::Recoverable_Warning) {
			_warn_log();
			Engine::Console::Warn("[A] ->"_D, err.name);
			if (!err.mess.empty()) { Engine::Console::Warn("[A] ->"_D, err.mess); }
		}
		else {
			_fail_log();
			Engine::Console::Error("[A] ->"_D, err.name);
			if (!err.mess.empty()) { Engine::Console::Error("[A] ->"_D, err.mess); }
		}

		if (err.type == Status::Recoverable_Error || err.type == Status::Recoverable_Warning) {
			if (!_rest(err.name)) {
				Engine::Console::Error("[A] ->"_D, "RecoveryHookFailed"_B);
				Engine::Console::Error("[A] ->"_D, "The system failed to restore its previous state."_D);

				return std::unexpected(Engine::Attempt::makeError("RecoveryHookFailed", "The recovery hook returned false."));
			}
			else {
				Engine::Console::Info("[A] ->"_D, "Recovery restored the program state."_D);
			}
		}
	}

	return _result;
}

template<typename Func, typename... Args>
inline Engine::Attempt::Runner<std::decay_t<Func>, std::decay_t<Args>...>
Engine::Attempt::to(Func&& func, Args&&... args) {
	return Runner<std::decay_t<Func>, std::decay_t<Args>...>(
		std::forward<Func>(func), std::forward<Args>(args)...);
}

#pragma endregion