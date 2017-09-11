//
// This class implements Workspace functionality in c++
//
//
// @author raver119@gmail.com
//

#ifndef LIBND4J_WORKSPACE_H
#define LIBND4J_WORKSPACE_H

#include <atomic>
#include <vector>
#include <mutex>
#include <pointercast.h>
#include <types/float16.h>

namespace nd4j {
    namespace memory {

        void ping();

        enum MemoryType {
            HOST,
            DEVICE,
        };

        class Workspace {
        protected:
            void* _ptrHost;
            void* _ptrDevice;

            std::atomic<Nd4jIndex> _offset;

            Nd4jIndex _initialSize;
            Nd4jIndex _currentSize;

            std::mutex _mutexAllocation;
            std::mutex _mutexSpills;

            std::vector<void*> _spills;

            std::atomic<Nd4jIndex> _spillsSize;

            void freeSpills();
        public:
            Workspace();
            Workspace(Nd4jIndex initialSize);
            ~Workspace();

            Nd4jIndex getCurrentSize();
            Nd4jIndex getCurrentOffset();
            Nd4jIndex getSpilledSize();

            bool resizeSupported();

            void* allocateBytes(Nd4jIndex numBytes);
            void* allocateBytes(MemoryType type, Nd4jIndex numBytes);

            void scopeIn();
            void scopeOut();
        };
    }
}

#endif //LIBND4J_WORKSPACE_H
