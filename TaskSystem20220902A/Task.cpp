#include "Task.h"
#include "TaskSystem.h"

Task::Task(Func&& func) noexcept
{
	SetFunction(std::forward<Func>(func));
}

Task::Task(const Task& task)
{
	m_funcs = task.m_funcs;
}

Task& Task::operator=(const Task& task)
{
	m_funcs = task.m_funcs;
	return *this;
}

void Task::Execute() noexcept
{
	// �֐����ݒ肳��Ă��Ȃ� Job �����s����Ă��鎞�A�����Ŏ~�܂�܂��B
	if (!m_funcs) { return; }

	m_funcs();
	m_finish = true;
}

void Task::SetFunction(Func&& func) noexcept
{
	m_finish = true;
	m_funcs = std::forward<Func>(func);
}

bool Task::IsTaskFinish() const noexcept
{
	return m_finish;
}

void Task::RegisterToJobSystem()
{
	m_finish = false;
	TaskSystem::Get().AddTask(this);
}