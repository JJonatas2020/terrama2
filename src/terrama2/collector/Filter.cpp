/*
  Copyright (C) 2007 National Institute For Space Research (INPE) - Brazil.

  This file is part of TerraMA2 - a free and open source computational
  platform for analysis, monitoring, and alert of geo-environmental extremes.

  TerraMA2 is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License,
  or (at your option) any later version.

  TerraMA2 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with TerraMA2. See LICENSE. If not, write to
  TerraMA2 Team at <terrama2-team@dpi.inpe.br>.
*/

/*!
  \file terrama2/collector/Filter.cpp

  \brief Filters data.

  \author Jano Simas
*/

#include "Filter.hpp"

struct terrama2::collector::Filter::Impl
{
    std::string mask_;
    te::gm::GeometryShrPtr  geometry_;
    te::gm::SpatialRelation relationRule_;
};

QStringList terrama2::collector::Filter::filterNames(const QStringList& namesList) const
{
  //TODO: Implement filterNames
  if(impl_->mask_.empty())
    return namesList;

  QStringList matchNames;
  for(const QString &name : namesList)
  {
    //TODO: how is the match? regex?
    if(name.toStdString() == impl_->mask_)
      matchNames.append(name);
  }

  return matchNames;
}

std::shared_ptr<te::da::DataSet> terrama2::collector::Filter::filterDataSet(const std::shared_ptr<te::da::DataSet> &dataSet) const
{
  //TODO: Implement filterDataSet
  return dataSet;
}


terrama2::collector::Filter::Filter()
{
  impl_ = new Impl();
  impl_->relationRule_ = te::gm::UNKNOWN_SPATIAL_RELATION;
}

terrama2::collector::Filter::~Filter()
{
  delete impl_;
}

void terrama2::collector::Filter::setMask(const std::string &mask)
{
  impl_->mask_ = mask;
}
