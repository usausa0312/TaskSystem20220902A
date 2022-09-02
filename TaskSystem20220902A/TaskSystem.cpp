#include "TaskSystem.h"
#include "Task.h"

TaskSystem::~TaskSystem()
{
	m_jthreads.clear();
	m_jthreads.shrink_to_fit();
}

bool TaskSystem::Initialize(int threadCount) noexcept
{
	if (threadCount < 0) { return false; };
	if (threadCount >= GetMaxThreadCount()) { return false; };

	if (m_isRunning)
		return true;

	m_isRunning = true;
	for (int i = 0; i < threadCount; ++i)
	{
		m_jthreads.emplace_back(&TaskSystem::ThreadLoop, this);
	}
	return true;
}

int TaskSystem::GetMaxThreadCount() const noexcept
{
	return std::jthread::hardware_concurrency();
}

void TaskSystem::AddTask(Task* job) noexcept
{
	m_tasks.emplace(job);
	m_cond.notify_one();
}

void TaskSystem::ThreadLoop() noexcept
{
	std::stop_source ss;
	std::stop_token stoken = ss.get_token();
	// ’âŽ~—v‹‚ª‚È‚³‚ê‚é‚Ü‚Åƒ‹[ƒv
	while (!stoken.stop_requested())
	{
		std::unique_lock lck(m_mutex);
		m_cond.wait(lck, [this] { return !m_tasks.empty() || !m_isRunning; });
		if (m_tasks.empty() && !m_isRunning)
			return;
		auto task = std::move(m_tasks.front());
		m_tasks.pop();
		lck.unlock();
		task->Execute();
	}
}