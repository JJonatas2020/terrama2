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
  \file terrama2/services/alert/impl/NotifierEmail.cpp

  \brief

  \author Jano Simas
          Vinicius Campanha
*/

// TerraMA2
#include "NotifierEmail.hpp"
#include "Utils.hpp"

#include "../core/SimpleCertificateVerifier.hpp"
#include "../core/Report.hpp"

vmime::shared_ptr <vmime::net::session> terrama2::services::alert::impl::NotifierEmail::session_ = vmime::net::session::create();

terrama2::services::alert::impl::NotifierEmail::NotifierEmail(const std::map<std::string, std::string>& serverMap, core::ReportPtr report)
    : Notifier(serverMap, report)
{

}

void terrama2::services::alert::impl::NotifierEmail::send(std::string recipient, int riskLevel, bool notifyOnChange) const
{
  vmime::messageBuilder mb;

  // Fill in the basic fields
  mb.setExpeditor(vmime::mailbox("vmimeteste@gmail.com"));
  vmime::addressList to;
  to.appendAddress(vmime::make_shared <vmime::mailbox>("vinicampa@gmail.com"));
  mb.setRecipients(to);
  mb.setSubject(vmime::text(report_->title()));

  std::string body;

  body = "<b>" + report_->author() + "</b><br/>";
  body += report_->abstract() + "<br/>";
  body += report_->description() + "<br/>";


  body+= terrama2::services::alert::core::dataSetHtmlTable(report_->retrieveData());

  body += report_->copyright() + "<br/>";

  mb.constructTextPart(vmime::mediaType(vmime::mediaTypes::TEXT, vmime::mediaTypes::TEXT_HTML));
  vmime::shared_ptr<vmime::htmlTextPart> textPart = vmime::dynamicCast<vmime::htmlTextPart>(mb.getTextPart());
  textPart->setCharset(vmime::charsets::ISO8859_15);

  textPart->setText(vmime::make_shared <vmime::stringContentHandler>(body));

  // Message body
//  mb.getTextPart()->setText(vmime::make_shared <vmime::stringContentHandler>(body));

  // Construction
  vmime::shared_ptr <vmime::message> msg = mb.construct();

  // email server
  vmime::utility::url url("smtp://smtp.gmail.com:587");
  vmime::shared_ptr<vmime::net::transport> tr = session_->getTransport(url);
  tr->setProperty("connection.tls", true);
  tr->setProperty("auth.username", "vmimeteste@gmail.com");
  tr->setProperty("auth.password", "a1a2a3a4");
  tr->setProperty("options.need-authentication", true);

  tr->setCertificateVerifier(vmime::make_shared<SimpleCertificateVerifier>());
  tr->connect();
  tr->send(msg);
}


