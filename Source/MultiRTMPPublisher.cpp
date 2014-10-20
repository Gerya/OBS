#include "Main.h"
#include "RTMPStuff.h"
#include "MultiRTMPPublisher.h"
#include "RTMPPublisher.h"


MultiRTMPPublisher::MultiRTMPPublisher()
{
	this->pMainPublisher.reset(new RTMPPublisher(false));
	if (AppConfig->GetString(TEXT("Publish"), TEXT("URL_BACKUP")).IsValid()){
		this->pBackupPublisher.reset(new RTMPPublisher(true));
	}	
}

MultiRTMPPublisher::~MultiRTMPPublisher()
{
	this->pMainPublisher.reset();
	if (this->pBackupPublisher){
		this->pBackupPublisher.reset();
	}
}

void MultiRTMPPublisher::SendPacket(BYTE *data, UINT size, DWORD timestamp, PacketType type) { 
	if (this->pMainPublisher){
		this->pMainPublisher->SendPacket(data, size, timestamp, type);
	}
	if (this->pBackupPublisher){
		this->pBackupPublisher->SendPacket(data, size, timestamp, type);
	}
}
void MultiRTMPPublisher::ResetChannel(){
	if (this->pBackupPublisher->isFailed){
		this->pBackupPublisher.reset();
		this->pBackupPublisher.reset(new RTMPPublisher(true));
		//this->pBackupPublisher = new RTMPPublisher(true);
	}
	if (this->pMainPublisher->isFailed){
		this->pMainPublisher.reset();
		this->pMainPublisher.reset(new RTMPPublisher(false));
		//this->pMainPublisher = new RTMPPublisher(false);
	}
}
double MultiRTMPPublisher::GetPacketStrain() const { 
	double result = 0;
	if(this->pMainPublisher)
		result = this->pMainPublisher->GetPacketStrain();
	if (this->pBackupPublisher){
		result += this->pBackupPublisher->GetPacketStrain();
	}
	return result;
}
QWORD MultiRTMPPublisher::GetCurrentSentBytes() {
	QWORD result = 0;
	if(this->pMainPublisher)
		result = this->pMainPublisher->GetCurrentSentBytes();
	if (this->pBackupPublisher){
		result += this->pBackupPublisher->GetCurrentSentBytes();
	}
	return result;
}
DWORD MultiRTMPPublisher::NumDroppedFrames() const {
	DWORD result = 0;
	if (this->pMainPublisher)
		result = this->pMainPublisher->NumDroppedFrames();
	if (this->pBackupPublisher){
		result += this->pBackupPublisher->NumDroppedFrames();
	}
	return result;
}
DWORD MultiRTMPPublisher::NumTotalVideoFrames() const {
	DWORD result = 0;
	if(this->pMainPublisher)
		result = this->pMainPublisher->NumTotalVideoFrames();
	if (this->pBackupPublisher){
		result += this->pBackupPublisher->NumTotalVideoFrames();
	}
	return result;
}


