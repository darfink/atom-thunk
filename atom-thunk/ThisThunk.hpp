#pragma once

#include <atom-thunk/ABI.hpp>
#include <cstring>
#include <memory>
#include <vector>

namespace atom {
  class ThisThunk {
  public:
    /* Constructs a context thunk
     *
     * @method The address of the target
     * @context The context for the target
     * @cc The calling convention of the caller
     */
    ThisThunk(void* method, void* context, CallingConvention cc);

    /* Retrieves the generated thunk
     *
     * @return The thunk's address
     */
    void* GetThunk() const;

  private:
    /* Generates a byte thunk
     *
     * This is OS specific (ABI)
     */
    void GenerateThunk(std::vector<unsigned char>& thunk);

    // Private members
    std::shared_ptr<void> mMemory;
    CallingConvention mConvention;
    void* mContext;
    void* mMethod;
  };

  inline void* ThisThunk::GetThunk() const {
    return mMemory.get();
  }
}

namespace {
  /* Appends data to a byte vector
   *
   * This method is used for easily appending data bytewise to a vector
   * consisting of unsigned characters. It makes opcode construction a breeze.
   *
   * @buffer The vector to manipulate
   * @data The data to append
   */
  template <typename T>
  std::vector<unsigned char>& operator<<(std::vector<unsigned char>& buffer, T data) {
    size_t size = buffer.size();

    buffer.resize(size + sizeof(T));
    std::memcpy(&buffer[size - 1], reinterpret_cast<unsigned char*>(&data), sizeof(T));

    return buffer;
  }
}
