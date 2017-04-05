var AbstractData = require("./AbstractData");


var DataProvider = function(params) {
  AbstractData.apply(this, [{'class': 'DataProvider'}]);

  this.id = params.id;
  this.project_id = params.project_id;
  this.description = params.description;
  this.data_provider_type_name = params.data_provider_type_name;
  this.data_provider_intent_id = params.data_provider_intent_id;

  if (params.DataProviderType)
    this.data_provider_type = params.DataProviderType.get();
  else if (params.data_provider_type)
    this.data_provider_type = params.data_provider_type;
  else
    this.data_provider_type = {};

  if (params.DataProviderConfigurations){
    params.DataProviderConfigurations.forEach(function(dataProviderConfiguration){
      var dPObject = dataProviderConfiguration.get();
      params[dPObject.key] = dPObject.value;
    });
  }

  if (params.timeout) {
    this.timeout = params.timeout;
  }

  if (params.active_mode) {
    this.active_mode = typeof params.active_mode == "boolean" ? params.active_mode : params.active_mode == "true";
  }

  this.name = params.name;
  this.active = params.active;
  this.uri = params.uri;
};

DataProvider.prototype = Object.create(AbstractData.prototype);
DataProvider.prototype.constructor = DataProvider;

DataProvider.prototype.toObject = function() {
  return Object.assign(AbstractData.prototype.toObject.call(this), {
    id: this.id,
    project_id: this.project_id,
    data_provider_type: this.data_provider_type.name,
    intent: this.data_provider_intent_id,
    name: this.name,
    timeout: this.timeout,
    active_mode: this.active_mode,
    description: this.description,
    //uri: decodeURIComponent(this.uri),
    uri: this.uri,
    active: this.active
  });
};

DataProvider.prototype.rawObject = function() {
  return {
    id: this.id,
    project_id: this.project_id,
    data_provider_type: this.data_provider_type,
    data_provider_intent_id: this.data_provider_intent_id,
    name: this.name,
    timeout: this.timeout,
    active_mode: this.active_mode,
    description: this.description,
    uri: this.uri,
    active: this.active
  };
};

module.exports = DataProvider;
