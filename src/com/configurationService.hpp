#pragma once

#include "comInterface.hpp"
#include "../utils/itcTask.hpp"

namespace dh {

class ConfigurationService : 	public ItcTask<ComMessage>,
				public ComHandlerInterface
{

public:
	ConfigurationService(std::shared_ptr<ComInterface> argComManager);
	virtual ~ConfigurationService();
	int initialize();
	virtual bool handleMessageCallback(std::shared_ptr<ComMessage> argComMessage) override;
	virtual bool handleMessage(std::shared_ptr<ComMessage> argMessage) override;
private:
	std::shared_ptr<ComInterface> comService;
	std::vector<int> subscriptionHandles;

};
}
