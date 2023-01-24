//
// Created by gcw on 23-1-24.
//

#ifndef CLION_POOLOPERATION_H
#define CLION_POOLOPERATION_H
#include <queue>
#include <vector>
#include <string>
#include "fileOperation.h"
#include <map>
#include <unordered_map>
#include <deque>
#include <memory>
#include <mutex>
#include <condition_variable>

using std::queue;
using std::vector;
using std::string;
using std::map;
using std::unordered_map;
using std::deque;
#define BASE_POOL_SIZE 20;//基础池数量
#define POOL_URL "/home/gcw/Construct_helper/judge_pool/"
#define JUDGE_LOG "/home/gcw/Construct_helper/log/judge"
#define NEW_POOL_DIR_ERROR 1001;
#define NEW_POOL_TXT_ERROR 1002;

#define DELETE_POOL_DIR_ERROR 2001;
#define DELETE_POOL_TXT_ERROR 2002;
#define DELETE_POOL_ERROR 2003;//执行删除时没有删除标记

//并发队列

template<typename DATATYPE, typename SEQUENCE = std::deque<DATATYPE>>
class ConcurrenceQueue {
public:
    ConcurrenceQueue() = default;

    ConcurrenceQueue(const ConcurrenceQueue & other) {
        std::lock_guard<std::mutex> lg(other.m_mutex);
        m_data = other.m_data;
    }
    ConcurrenceQueue(ConcurrenceQueue &&) = delete;
    ConcurrenceQueue & operator= (const ConcurrenceQueue &) = delete;
    ~ConcurrenceQueue() = default;
    bool empty() const {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_data.empty();
    }

    void push(const DATATYPE & data) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.push(data);
        m_cond.notify_one();
    }

    void push(DATATYPE && data) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.push(std::move(data));
        m_cond.notify_one();
    }

    std::shared_ptr<DATATYPE> tryPop() {  // 非阻塞
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_data.empty()) return {};
        auto res = std::make_shared<DATATYPE>(m_data.front());
        m_data.pop();
        return res;
    }

    std::shared_ptr<DATATYPE> pop() {  // 非阻塞
        std::unique_lock<std::mutex> lg(m_mutex);
        m_cond.wait(lg, [this] { return !m_data.empty(); });
        auto res = std::make_shared<DATATYPE>(std::move(m_data.front()));
        m_data.pop();
        return res;
    }

private:
    std::queue<DATATYPE, SEQUENCE> m_data;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
};
ConcurrenceQueue<int>q;

class Judge_poolOperator{
public:
    int pool_size;
    Judge_poolOperator();
    ~Judge_poolOperator();
    static int create_pool(int);
    static int delete_pool(int);

    //返回一个池标记,如果为-1表示分配失败
    static int get_pool(string &s);
    //释放一个池标记,成功返回0
    static int free_pool(int id);


}judge_poolOperator;


//init
Judge_poolOperator::Judge_poolOperator() {
    pool_size=BASE_POOL_SIZE;
    //create_dir
    for(int i=1;i<=pool_size;i++){
        create_pool(i);
        q.push(i);
    }
}
Judge_poolOperator::~Judge_poolOperator() {
    for(int i=1;i<=pool_size;i++){
        delete_pool(i);
    }
}
int Judge_poolOperator::create_pool(int i) {
    if(!FileOperator::exists_dir(POOL_URL+to_string(i)))
        FileOperator::create_dir(POOL_URL+to_string(i));
    else{
        //return NEW_POOL_DIR_ERROR;
    }

    if(!FileOperator::exists_txt(POOL_URL+ to_string(i)+"/"+"data.in")){
        FileOperator::create_txt(POOL_URL+ to_string(i)+"/"+"data.in");
    }else{
        //return NEW_POOL_TXT_ERROR;
    }


    if(!FileOperator::exists_txt(POOL_URL+ to_string(i)+"/"+"data.out")){
        FileOperator::create_txt(POOL_URL+ to_string(i)+"/"+"data.out");
    }else{
        //return NEW_POOL_TXT_ERROR;
    }

    if(!FileOperator::exists_txt(POOL_URL+ to_string(i)+"/"+"err.txt")){
        FileOperator::create_txt(POOL_URL+ to_string(i)+"/"+"err.txt");
    }else{
        //return NEW_POOL_TXT_ERROR;
    }
    q.push(i);
    return 0;
}

int Judge_poolOperator::delete_pool(int i) {
    if(FileOperator::exists_dir(POOL_URL+to_string(i)))
        FileOperator::delete_dir(POOL_URL+to_string(i));
    else{
       // return DELETE_POOL_DIR_ERROR;
    }

    if(FileOperator::exists_txt(POOL_URL+ to_string(i)+"/"+"data.in")){
        FileOperator::delete_file(POOL_URL+ to_string(i)+"/"+"data.in");
    }else{
        //return DELETE_POOL_TXT_ERROR;
    }


    if(!FileOperator::exists_txt(POOL_URL+ to_string(i)+"/"+"data.out")){
        FileOperator::delete_file(POOL_URL+ to_string(i)+"/"+"data.out");
    }else{
        //return DELETE_POOL_TXT_ERROR;
    }

    if(!FileOperator::exists_txt(POOL_URL+ to_string(i)+"/"+"err.txt")){
        FileOperator::delete_file(POOL_URL+ to_string(i)+"/"+"err.txt");
    }else{
        //return DELETE_POOL_TXT_ERROR;
    }
    return 0;
}

int Judge_poolOperator::get_pool(string &s) {
    if(q.empty())
        return -1;
    shared_ptr<int> id=q.pop();
    s=POOL_URL+to_string(*id);
    return *id;
}

int Judge_poolOperator::free_pool(int id) {
    q.push(id);
    return 0;
}




#endif //CLION_POOLOPERATION_H
