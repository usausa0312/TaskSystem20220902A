#pragma once
#include <chrono>
#include <iostream>
#include <stop_token> 
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
class Task;

class TaskSystem
{
	TaskSystem() = default;
	TaskSystem(const TaskSystem&) = delete;
	TaskSystem& operator=(const TaskSystem&) = delete;
public:
	static TaskSystem& Get() {
		static TaskSystem instane;
		return instane;
	}

	~TaskSystem();

	/** �w��� thread �������������B*/
	bool Initialize(int threadCount) noexcept;

	/** ���񏈗��Ŏ��s����鏈���̒ǉ��B*/
	void AddTask(Task* job) noexcept;

	/** CPU�ő�g�p�\�X���b�h����Ԃ��B*/
	int GetMaxThreadCount() const noexcept;

private:
	/** �C���X�^���X�̉�����Ɏ��s�����B*/
	//void Stop() noexcept;
	/** �������ꂽ�e thread ���������� Task ���s���s���֐��B*/
	void ThreadLoop() noexcept;
private:
	// * ���񏈗����̏I�����Ǘ�����
	bool m_isRunning = false;

	// * �^�X�N���s����Ă��Ȃ� thread ����ێ�
	int m_numOfThreadsAvailable = 0;


	std::queue<Task*> m_tasks;
	// * ���[�U�[�w�萔�� thread ����ύX���邽�߂ɉϒ��z��ŊǗ�
	std::vector<std::jthread> m_jthreads;
	// �X���b�h����p
	std::mutex m_mutex;
	std::condition_variable_any m_cond;
};
