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

#ifndef IROHA_SHARED_MODEL_REMOVE_SIGNATORY_HPP
#define IROHA_SHARED_MODEL_REMOVE_SIGNATORY_HPP

#include "interfaces/common_objects/types.hpp"
#include "interfaces/primitive.hpp"
#include "model/commands/remove_signatory.hpp"

namespace shared_model {
  namespace interface {
    /**
     * Remove signatory from the account
     */
    class RemoveSignatory
        : public Primitive<RemoveSignatory, iroha::model::RemoveSignatory> {
     public:
      /**
       * @return account from which remove signatory
       */
      virtual const types::AccountIdType &accountId() const = 0;
      /**
       * @return Public key to remove from account
       */
      virtual const types::PubkeyType &pubkey() const = 0;
    };
  }  // namespace interface
}  // namespace shared_model

#endif  // IROHA_SHARED_MODEL_REMOVE_SIGNATORY_HPP