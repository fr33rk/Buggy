using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PL.Common.Socket;

namespace PL.BuggySoft.Business.Services
{
	public class BuggyCommunicationService
	{
		private ISender mSender;

		public BuggyCommunicationService(ISender sender)
		{
			mSender = sender;
			mSender.OnConnect += SenderOnOnConnect; 
			mSender.OnDataReceived += SenderOnOnDataReceived;
			mSender.OnDisconnect += SenderOnOnDisconnect;
		}

		private void SenderOnOnDisconnect(object sender, EventArgs eventArgs)
		{
			throw new NotImplementedException();
		}

		private void SenderOnOnConnect(object sender, EventArgs eventArgs)
		{
			throw new NotImplementedException();
		}

		private void SenderOnOnDataReceived(object sender, SocketDataReceivedEventArgs socketDataReceivedEventArgs)
		{
			throw new NotImplementedException();
		}



		public void Connect()
		{
			mSender?.Start();
		}
	}
}
