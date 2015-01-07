#include <iostream>
#include <string>
#include <vector>

std::vector<int> campaignIds;
std::vector<int> lineItemIds;
std::vector<int> creativeIds;

class campaign {
	private:
		std::string campaignName;
		int campaignId;
		std::vector<int> lineItems;
	public:
		campaign() {
			int y = campaignIds.back();
			campaignIds.push_back(y+1);
			campaignId = campaignIds.back();
		};
		campaign(std::string x) {
			campaignName = x;
			int y = campaignIds.back();
			campaignIds.push_back(y+1);
			campaignId = campaignIds.back();
		};
		int getCampaignId(void) {
			return campaignId;
		}
		std::string getCampaignName(void) {
			return campaignName;
		}
};

class lineItem : public campaign {
	private:
		std::string lineItemName;
		int lineItemId;
		std::vector<int> creatives;
		int inventorySource;
	public:
		lineItem() {
			int y = lineItemIds.back();
			lineItemIds.push_back(y+1);
			lineItemId = lineItemIds.back();
		};
		lineItem(std::string x) {
			lineItemName = x;
			int y = lineItemIds.back();
			lineItemIds.push_back(y+1);
			lineItemId = lineItemIds.back();
		};
};

class creative : public lineItem {
	private:
		std::string creativeName;
		int creativeId;
		std::string creativeData;
	public:
		creative() {
			int y = creativeIds.back();
			creativeIds.push_back(y+1);
			creativeId = creativeIds.back();
		};
		creative(std::string x) {
			creativeName = x;
			int y = creativeIds.back();
			creativeIds.push_back(y+1);
			creativeId = creativeIds.back();
		}
};

struct inventory {
	std::string name;
};

int main() {
	campaignIds.push_back(0);

	campaign campaign1("Campaign 1");



	return 0;
}