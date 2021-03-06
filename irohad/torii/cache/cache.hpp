/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_CACHE_HPP
#define IROHA_CACHE_HPP

#include <unordered_map>
#include "torii/cache/abstract_cache.hpp"

namespace iroha {
  namespace cache {
    template <typename KeyType, typename ValueType>
    class Cache
        : public AbstractCache<KeyType, ValueType, Cache<KeyType, ValueType>> {
     public:
      uint32_t getIndexSizeHighImpl() const {
        return MAX_HANDLER_MAP_SIZE_HIGH;
      }

      uint32_t getIndexSizeLowImpl() const { return MAX_HANDLER_MAP_SIZE_LOW; }

      uint32_t getCacheItemCountImpl() const {
        return (uint32_t)handler_map_.size();
      }

      void addItemImpl(const KeyType &key, const ValueType &value) {
        // elements with the same hash should be replaced
        handler_map_[key] = value;
        handler_map_index_.push_back(key);
        if (handler_map_.size() > getIndexSizeHighImpl()) {
          while (handler_map_.size() > getIndexSizeLowImpl()) {
            handler_map_.erase(handler_map_index_.front());
            handler_map_index_.pop_front();
          }
        }
      }

      boost::optional<ValueType> findItemImpl(const KeyType &key) const {
        auto found = handler_map_.find(key);
        if (found == handler_map_.end()) {
          return boost::none;
        } else {
          return handler_map_.at(key);
        }
      }

     private:
      std::unordered_map<KeyType, ValueType> handler_map_;
      std::list<KeyType> handler_map_index_;

      /**
      * Protection from handler map overflow.
      * TODO 27/10/2017 luckychess Values are quite random and should be tuned
      * for better performance and may be even move to config IR-579
      */
      const uint32_t MAX_HANDLER_MAP_SIZE_HIGH = 20000;
      const uint32_t MAX_HANDLER_MAP_SIZE_LOW = 10000;
    };
  }
}

#endif  // IROHA_CACHE_HPP
