#ifndef __BUFFER_POOL_HPP__
#define __BUFFER_POOL_HPP__

template <typename T>
class BufferPool
{
public :
        typedef T value_type;
        typedef T* value_ptr;

        bool init(size_t buffer_size, size_t count)
        {
                buffer_list_.reserve(count);
                for (size_t i=0; i<count; ++i)
                        buffer_list_.push_back(CREATE_BUFFER_PTR);

                max_pos_ = buffer_list_.size();
                cur_pos_ = 0;
                max_buffer_size_ = buffer_size;

                return true;
        }

        inline value_ptr malloc_buffer()
        {
                value_ptr ret = nullptr;
                {
                        std::lock_guard<std::mutex> lock(mutex_);
                        if (cur_pos_ < max_pos_)
                                ret = buffer_list_[cur_pos_++];
                }
                return ret;
        }

        inline void free_buffer(value_ptr buff)
        {
                {
                        std::lock_guard<std::mutex> lock(mutex_);
                        if (cur_pos_ >= 0)
                                buffer_list_[cur_pos_--] = buff;
                }
        }

        void resize(size_t count)
        {
                std::lock_guard<std::mutex> lock(mutex_);
                for (size_t i=0; i<count; ++i)
                        buffer_list_.push_back(new T[max_buffer_size_]);
                max_pos_ = buffer_list_.size();
        }

private :
        std::vector<value_ptr> buffer_list_;
        size_t max_pos_;
        size_t cur_pos_;
        size_t max_buffer_size_;
        std::mutex mutex_;
};

#endif // __BUFFER_POOL_HPP__
