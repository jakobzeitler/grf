/*-------------------------------------------------------------------------------
  This file is part of gradient-forest.

  gradient-forest is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  gradient-forest is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with gradient-forest. If not, see <http://www.gnu.org/licenses/>.
 #-------------------------------------------------------------------------------*/

#include "Data.h"
#include "Forest.h"

Forest Forest::create(std::vector<std::shared_ptr<Tree>> trees,
                      Data* data,
                      std::unordered_map<std::string, size_t> observables) {
  std::map<std::string, std::vector<double>> observations_by_type;
  size_t num_samples = data->getNumRows();
  for (auto it : observables) {
    std::string type = it.first;
    size_t index = it.second;
    for (size_t row = 0; row < num_samples; row++) {
      observations_by_type[type].push_back(data->get(row, index));
    }
  }

  Observations observations(observations_by_type, num_samples);
  return Forest(trees, observations);
}

Forest::Forest(const std::vector<std::shared_ptr<Tree>>& trees,
               const Observations& observations):
  trees(trees), observations(observations) {}