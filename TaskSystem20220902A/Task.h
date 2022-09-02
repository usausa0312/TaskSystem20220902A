#pragma once
#include<functional>

class Task
{
	using Func = std::function<void()>;
public:

	Task() = default;
	Task(Func&& func) noexcept;

	Task(const Task&);
	Task& operator=(const Task&);

	void Execute() noexcept;

	/** JobSystem で実行される関数 function を設定。*/
	void SetFunction(Func&& func) noexcept;

	/** JobSystem で実行されるメンバ関数 function を設定。*/
	template<class T, class F>
	void SetFunction(T* ptr, F task) noexcept;

	bool IsTaskFinish() const noexcept;

	/** 実行する処理をタスクに追加。*/
	void RegisterToJobSystem();

private:

	// * 非同期実行させるタスク処理。
	Func m_funcs;

	// * タスク処理が完了したかを保持する。
	std::atomic_bool m_finish;
};

template<class T, class F>
inline void Task::SetFunction(T* ptr, F func) noexcept
{
	m_funcs = std::bind(&func, ptr);
}