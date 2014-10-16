#include "Main.h"
#include "RTMPStuff.h"
#include "MultiRTMPPublisher.h"
#include "RTMPPublisher.h"


MultiRTMPPublisher::MultiRTMPPublisher()
{
	this->pMainPublisher = new RTMPPublisher(false);
	if (AppConfig->GetString(TEXT("Publish"), TEXT("URL_BACKUP")).IsValid()){
		this->pBackupPublisher = new RTMPPublisher(true);
	}	
}

MultiRTMPPublisher::~MultiRTMPPublisher()
{
	delete this->pMainPublisher;
	if (this->pBackupPublisher != NULL){
		delete this->pBackupPublisher;
	}
}

void MultiRTMPPublisher::SendPacket(BYTE *data, UINT size, DWORD timestamp, PacketType type) { 
	this->pMainPublisher->SendPacket(data, size, timestamp, type);
	if (this->pBackupPublisher != NULL){
		this->pBackupPublisher->SendPacket(data, size, timestamp, type);
	}
}

double MultiRTMPPublisher::GetPacketStrain() const { 
	double result = this->pMainPublisher->GetPacketStrain();
	if (this->pBackupPublisher!= NULL){
		result += this->pBackupPublisher->GetPacketStrain();
	}
	return result;
}
QWORD MultiRTMPPublisher::GetCurrentSentBytes() {
	QWORD result = this->pMainPublisher->GetCurrentSentBytes();
	if (this->pBackupPublisher != NULL){
		result += this->pBackupPublisher->GetCurrentSentBytes();
	}
	return result;
}
DWORD MultiRTMPPublisher::NumDroppedFrames() const {
	DWORD result = this->pMainPublisher->NumDroppedFrames();
	if (this->pBackupPublisher != NULL){
		result += this->pBackupPublisher->NumDroppedFrames();
	}
	return result;
}
DWORD MultiRTMPPublisher::NumTotalVideoFrames() const {
	DWORD result = this->pMainPublisher->NumTotalVideoFrames();
	if (this->pBackupPublisher != NULL){
		result += this->pBackupPublisher->NumTotalVideoFrames();
	}
	return result;
}


