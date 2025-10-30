// define templated -unknown typed classes and functions within header file to avoid liknking exceptions.

template<typename T,typename ... Arg> void Common::__recurse_output(T item,Arg ...args){
	std::cout << item << " ";
	__recurse_output(args...);
}

inline void Common::__recurse_output(){
	std::cout << std::endl;
}

template<Common::Console::LogPriority P,typename T,typename ...Args>
void Common::Console::Log(T msg,Args ...args) {
	__recurse_output(
		__get_banner<P>(
		COMMON_CONSOLE_BA_LOG,
		COMMON_CONSOLE_FG_LOG,
		COMMON_CONSOLE_BG_LOG,
		COMMON_CONSOLE_XX_LOG
	),":",msg,args...
	);
}

template<Common::Console::LogPriority P,typename T,typename ...Args>
void Common::Console::Info(T msg,Args ...args) {
	__recurse_output(
		__get_banner<P>(
		COMMON_CONSOLE_BA_INF,
		COMMON_CONSOLE_FG_INF,
		COMMON_CONSOLE_BG_INF,
		COMMON_CONSOLE_XX_INF
	),":",msg,args...
	);
}

template<Common::Console::LogPriority P,typename T,typename ...Args>
void Common::Console::Debug(T msg,Args ...args) {
	__recurse_output(
		__get_banner<P>(
		COMMON_CONSOLE_BA_DBG,
		COMMON_CONSOLE_FG_DBG,
		COMMON_CONSOLE_BG_DBG,
		COMMON_CONSOLE_XX_DBG
	),":",msg,args...
	);
}

template<Common::Console::LogPriority P,typename T,typename ...Args>
void Common::Console::Warn(T msg,Args ...args) {
	__recurse_output(
		__get_banner<P>(
		COMMON_CONSOLE_BA_WRN,
		COMMON_CONSOLE_FG_WRN,
		COMMON_CONSOLE_BG_WRN,
		COMMON_CONSOLE_XX_WRN
	),":",msg,args...
	);
}

template<Common::Console::LogPriority P,typename T,typename ...Args>
void Common::Console::Error(T msg,Args ...args) {
	__recurse_output(
		__get_banner<P>(
		COMMON_CONSOLE_BA_ERR,
		COMMON_CONSOLE_FG_ERR,
		COMMON_CONSOLE_BG_ERR,
		COMMON_CONSOLE_XX_ERR
	),":",msg,args...
	);
}
