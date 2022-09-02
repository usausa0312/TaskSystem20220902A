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

	/** 指定個数 thread を処理初期化。*/
	bool Initialize(int threadCount) noexcept;

	/** 並列処理で実行される処理の追加。*/
	void AddTask(Task* job) noexcept;

	/** CPU最大使用可能スレッド数を返す。*/
	int GetMaxThreadCount() const noexcept;

private:
	/** インスタンスの解放時に実行される。*/
	//void Stop() noexcept;
	/** 生成された各 thread が処理する Task 実行を行う関数。*/
	void ThreadLoop() noexcept;
private:
	// * 並列処理中の終了を管理する
	bool m_isRunning = false;

	// * タスク実行されていない thread 数を保持
	int m_numOfThreadsAvailable = 0;


	std::queue<Task*> m_tasks;
	// * ユーザー指定数で thread 数を変更するために可変長配列で管理
	std::vector<std::jthread> m_jthreads;
	// スレッド操作用
	std::mutex m_mutex;
	std::condition_variable_any m_cond;
};
