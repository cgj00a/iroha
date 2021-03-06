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

#ifndef IROHA_SHARED_MODEL_SUBTRACT_ASSET_QUANTITY_HPP
#define IROHA_SHARED_MODEL_SUBTRACT_ASSET_QUANTITY_HPP

#include "interfaces/base/primitive.hpp"
#include "interfaces/common_objects/amount.hpp"
#include "interfaces/common_objects/types.hpp"
#include "model/commands/subtract_asset_quantity.hpp"

namespace shared_model {
  namespace interface {

    /**
     * Subtract amount of asset from an account
     */
    class SubtractAssetQuantity
        : public Primitive<SubtractAssetQuantity,
                           iroha::model::SubtractAssetQuantity> {
     public:
      /**
       * @return Identity of user to subtract quantity from
       */
      virtual const types::AccountIdType &accountId() const = 0;
      /**
       * @return asset identifier
       */
      virtual const types::AssetIdType &assetId() const = 0;
      /**
       * @return quantity of asset for subtracting
       */
      virtual const Amount &amount() const = 0;

      std::string toString() const override {
        return detail::PrettyStringBuilder()
            .init("SubtractAssetQuantity")
            .append("account_id", accountId())
            .append("asset_id", assetId())
            .append("amount", amount().toString())
            .finalize();
      }

      OldModelType *makeOldModel() const override {
        auto oldModel = new iroha::model::SubtractAssetQuantity;
        using OldAmountType = iroha::Amount;
        /// Use shared_ptr and placement-new to copy new model field to
        /// oldModel's field and to return raw pointer
        auto p = std::shared_ptr<OldAmountType>(amount().makeOldModel());
        new (&oldModel->amount) OldAmountType(*p);
        oldModel->account_id = accountId();
        oldModel->asset_id = assetId();
        return oldModel;
      }

      bool operator==(const ModelType &rhs) const override {
        return accountId() == rhs.accountId() and assetId() == rhs.assetId()
            and amount() == rhs.amount();
      }
    };
  }  // namespace interface
}  // namespace shared_model

#endif  // IROHA_SHARED_MODEL_SUBTRACT_ASSET_QUANTITY_HPP
