/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_CORE_BASE_BUFFEREDLIFOQUEUE_H_
#define HESPERIA_CORE_BASE_BUFFEREDLIFOQUEUE_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/base/LIFOQueue.h"
#include "core/exceptions/Exceptions.h"

namespace core {
    namespace base {

        using namespace std;

        /**
         * This interface encapsulates all methods necessary for a buffered LIFO.
         * A buffered LIFO allows indexed access to the elements without removing
         * them.
         */
        class HESPERIA_API BufferedLIFOQueue : public LIFOQueue {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                BufferedLIFOQueue(const BufferedLIFOQueue &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                BufferedLIFOQueue& operator=(const BufferedLIFOQueue &);

            public:
                BufferedLIFOQueue();

                /**
                 * Constructor.
                 *
                 * @param bufferSize Maximum size for this buffered lifo.
                 */
                BufferedLIFOQueue(const uint32_t &bufferSize);

                virtual ~BufferedLIFOQueue();

                virtual void push(const data::Container &container);

                /**
                 * This method returns the index of the last element.
                 *
                 * @return Index of the last element or -1 if the LIFO is empty.
                 */
                int32_t getIndexOfLastElement() const;

                /**
                 * This method returns the elements at the current index.
                 *
                 * @param index Index of the element to be retrieved.
                 * @return Element at the given index.
                 * @throws ArrayIndexOutOfBoundsException if the index is invalid.
                 */
                const data::Container getElementAt(const uint32_t &index) const throw (exceptions::ArrayIndexOutOfBoundsException);

            private:
                uint32_t m_bufferSize;
        };

    }
} // core::base

#endif /*HESPERIA_CORE_BASE_BUFFEREDLIFOQUEUE_H_*/
