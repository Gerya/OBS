#include <Iphlpapi.h>

class MultiRTMPPublisher : public NetworkStream
{
public:
	MultiRTMPPublisher();
	~MultiRTMPPublisher();

	virtual void SendPacket(BYTE *data, UINT size, DWORD timestamp, PacketType type);

	double GetPacketStrain ()const;
	QWORD GetCurrentSentBytes();
	virtual DWORD NumDroppedFrames ()const;
	virtual DWORD NumTotalVideoFrames()const;

private:
	QWORD bytesSent;
	DWORD framesRendered;
	RTMPPublisher* pMainPublisher;
	RTMPPublisher* pBackupPublisher;
};
