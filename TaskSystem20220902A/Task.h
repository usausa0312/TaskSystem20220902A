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

	/** JobSystem �Ŏ��s�����֐� function ��ݒ�B*/
	void SetFunction(Func&& func) noexcept;

	/** JobSystem �Ŏ��s����郁���o�֐� function ��ݒ�B*/
	template<class T, class F>
	void SetFunction(T* ptr, F task) noexcept;

	bool IsTaskFinish() const noexcept;

	/** ���s���鏈�����^�X�N�ɒǉ��B*/
	void RegisterToJobSystem();

private:

	// * �񓯊����s������^�X�N�����B
	Func m_funcs;

	// * �^�X�N������������������ێ�����B
	std::atomic_bool m_finish;
};

template<class T, class F>
inline void Task::SetFunction(T* ptr, F func) noexcept
{
	m_funcs = std::bind(&func, ptr);
}