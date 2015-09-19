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
  \file terrama2/ws/collector/server/Collector.cpp

  \brief Aquire data from server.

  \author Jano Simas
*/


#include "Collector.hpp"
#include "../core/DataSet.hpp"

//Boost
#include <boost/log/trivial.hpp>


terrama2::collector::Collector::Collector(const terrama2::core::DataProviderPtr dataProvider, QObject *parent)
  : QObject(parent),
    dataProvider_(dataProvider)
{

}

terrama2::collector::Collector::~Collector()
{
  //If there is a thread running, join.
  if(collectingThread_.joinable())
    collectingThread_.join();
}

bool terrama2::collector::Collector::isCollecting() const
{
  //Test if is not locked
  if(mutex_.try_lock())
  {
    //if can lock no one is using and release lock
    mutex_.unlock();
    return false;
  }
  else
    //if cant get lock, is collecting
    return true;
}

void terrama2::collector::Collector::collectAsThread(const DataSetTimerPtr datasetTimer)
{
  //already locked by Collector::collect, lock_guar just to release when finished
  std::lock_guard<std::mutex> lock(mutex_, std::adopt_lock);
  //aquire all data
  for(auto& data : datasetTimer->data())
  {
    //TODO: conditions to collect Data?
    getData(data);
  }
}

void terrama2::collector::Collector::collect(const DataSetTimerPtr datasetTimer)
{
  if(datasetTimer->isValid())
  {
    //TODO: Collector::collect: throws dataset is invalid
  }

  if(datasetTimer->dataSet()->status() != terrama2::core::DataSet::ACTIVE)
  {
    //TODO: Collector::collect: throws dataset not active
  }

  //If can get lock creates a thread the collects the dataset
  if(!mutex_.try_lock())
  {
    //throws an exception: unable to get lock

    //TODO: Collector::collect: Exception if cant get mutex.lock
  }

  //***************************************************
  //nothing wrong, prepare and collect

  //"default" thread are not joinable,
  //if there was one and we got a lock it has ended than join
  if(collectingThread_.joinable())
    collectingThread_.join();

  //start a new thread
  collectingThread_ = std::thread(&Collector::collectAsThread, this, datasetTimer);
}