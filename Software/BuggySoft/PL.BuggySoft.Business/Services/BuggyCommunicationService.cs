﻿using System;
using System.Linq;
using PL.BuggySoft.Infrastructure.Models.Messages;
using PL.BuggySoft.Infrastructure.Services;
using PL.Common.Socket;
using PL.Logger;

namespace PL.BuggySoft.Business.Services
{
	/// <summary>Service that takes care of communicating with the buggy.
	/// </summary>
	public class BuggyCommunicationService : IBuggyCommunicationService
	{
		#region Definitions

		private ISender mSender;
		private readonly ILogFile mComLogFile;
		private ushort mTaskId;

		#endregion Definitions

		#region Constructor(s)

		/// <summary>Initializes a new instance of the <see cref="BuggyCommunicationService"/> class.
		/// </summary>
		/// <param name="comLogFile">The COM log file.</param>
		public BuggyCommunicationService(ILogFile comLogFile)
		{
			mComLogFile = comLogFile;
			comLogFile.WriteLogStart();
		}

		#endregion Constructor(s)

		#region Sender events

		protected virtual ISender CreateSender(string ip, int port)
		{
			var retValue = new Sender(mComLogFile, ip, port, 5000);

			return retValue;
		}

		private void SenderOnOnDisconnect(object sender, EventArgs eventArgs)
		{
			mComLogFile?.Info("Disconnected.");
			Disconnected?.Invoke(this, EventArgs.Empty);
			IsConnected = false;
		}

		private void SenderOnOnConnect(object sender, EventArgs eventArgs)
		{
			mComLogFile?.Info("Connected.");
			Connected?.Invoke(this, EventArgs.Empty);
			IsConnected = true;
		}

		private void SenderOnOnDataReceived(object sender, SocketDataReceivedEventArgs socketDataReceivedEventArgs)
		{
			// Convert the string containing Hex characters to a byte array.
			var rawMessage = Enumerable.Range(0, socketDataReceivedEventArgs.Data.Length-2)
				.Where(x => x % 2 == 0)
				.Select(x => Convert.ToByte(socketDataReceivedEventArgs.Data.Substring(x, 2), 16))
				.ToArray();

			var message = BuggyMessageFactory.CreateWrapperForRawMessage(rawMessage);

			if (message != null)
			{
				mComLogFile?.Info($"< {message}");
				MessageReceived?.Invoke(this, new MessageReceivedEventArgs<BaseBuggyMessageWrapper>(message));

				if (message is VersionMessageWrapper)
				{
					VersionMessageReceived?.Invoke(this, new MessageReceivedEventArgs<VersionMessageWrapper>(message as VersionMessageWrapper));
				}
			}
			else
			{
				mComLogFile?.Error($"Unknown message received: ({socketDataReceivedEventArgs.Data})");
			}
		}

		private void SendMessage(BaseBuggyMessageWrapper message)
		{
			mComLogFile?.Info($"> {message}");
			mSender.WriteAsync(BitConverter.ToString(message.ToRawMessage()).Replace("-", string.Empty));
			MessageSend?.Invoke(this, new MessageSendEventArgs(message));
		}

		#endregion Sender events

		#region Public methods

		public void Connect(string ip, int port)
		{
			mSender = CreateSender(ip, port);
			mSender.OnConnect += SenderOnOnConnect;
			mSender.OnDataReceived += SenderOnOnDataReceived;
			mSender.OnDisconnect += SenderOnOnDisconnect;
			mSender?.Start();
		}

		#region Commands

		public void RequestVersion()
		{
			SendMessage(new VersionRequestMessageWrapper(++mTaskId));
		}

		public void SteerMotor(sbyte left, sbyte right)
		{
			SendMessage(new SteerMotorMessageWrapper(++mTaskId, left, right));
		}

		public void RequestSensors(AnalogSensor sensor, bool continues = false)
		{
			SendMessage(new SensorRequestMessageWrapper(++mTaskId, sensor, continues));
		}

		public void GetErrors()
		{
			SendMessage(new ErrorRequestMessageWrapper(++mTaskId));
		}

		#endregion Commands

		public bool IsConnected { get; private set; }

		public event EventHandler Connected;

		public event EventHandler Disconnected;

		public event EventHandler<MessageReceivedEventArgs<BaseBuggyMessageWrapper>> MessageReceived;

		public event EventHandler<MessageReceivedEventArgs<VersionMessageWrapper>> VersionMessageReceived;

		public event EventHandler<MessageSendEventArgs> MessageSend;

		#endregion Public methods
	}
}