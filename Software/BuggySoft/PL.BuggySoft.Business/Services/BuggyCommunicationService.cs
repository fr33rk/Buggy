using System;
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

		#region Sender

		/// <summary>Create the required ISender object. Meant as a seem for unit testing.
		/// </summary>
		/// <param name="ip">IP address to connect to.</param>
		/// <param name="port">TCP/IP port to connect to.</param>
		/// <returns></returns>
		protected virtual ISender CreateSender(string ip, int port)
		{
			var retValue = new Sender(mComLogFile, ip, port, 5000);

			return retValue;
		}

		private void SenderOnOnDisconnect(object sender, EventArgs eventArgs)
		{
			IsConnected = false;
			mComLogFile?.Info("Disconnected.");
			Disconnected?.Invoke(this, EventArgs.Empty);
		}

		private void SenderOnOnConnect(object sender, EventArgs eventArgs)
		{
			IsConnected = true;
			mComLogFile?.Info("Connected.");
			Connected?.Invoke(this, EventArgs.Empty);
		}

		private void SenderOnOnDataReceived(object sender, SocketDataReceivedEventArgs socketDataReceivedEventArgs)
		{
			// Convert the string containing Hex characters to a byte array.
			var rawMessage = Enumerable.Range(0, socketDataReceivedEventArgs.Data.Length - 2)
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
			mSender.WriteAsync(BitConverter.ToString(message.ToRawMessage()).Replace("-", string.Empty) + "\r\n");
			MessageSend?.Invoke(this, new MessageSendEventArgs(message));
		}

		#endregion Sender

		#region IBuggyCommunicationService

		/// <summary>Start attempting to connect to the Buggy.
		/// </summary>
		/// <param name="ip"></param>
		/// <param name="port"></param>
		public void Connect(string ip, int port)
		{
			mSender = CreateSender(ip, port);
			mSender.OnConnect += SenderOnOnConnect;
			mSender.OnDataReceived += SenderOnOnDataReceived;
			mSender.OnDisconnect += SenderOnOnDisconnect;
			mSender?.Start();
		}

		/// <summary>Disconnect from the buggy.
		/// </summary>
		public void Disconnect()
		{
			mSender?.Stop();
		}

		/// <summary>
		/// Request the buggy to send its firmware version. Answer will be supplied via VersionMessageReceived event.
		/// </summary>
		public void RequestVersion()
		{
			SendMessage(new VersionRequestMessageWrapper(++mTaskId));
		}

		/// <summary>
		/// Steer the motors.
		/// </summary>
		/// <param name="left">The left speed and direction. Value between -100..100, negative is reverse.</param>
		/// <param name="right">The right speed and direction. Value between -100..100, negative is reverse.</param>
		public void SteerMotor(sbyte left, sbyte right)
		{
			SendMessage(new SteerMotorMessageWrapper(++mTaskId, left, right));
		}

		/// <summary>
		/// Requests the readout of the selected sensor(s).
		/// </summary>
		/// <param name="sensor">The sensor.</param>
		/// <param name="continues">if set to <c>true</c> [continues].</param>
		public void RequestSensors(AnalogSensor sensor, bool continues = false)
		{
			SendMessage(new SensorRequestMessageWrapper(++mTaskId, sensor, continues));
		}

		/// <summary>
		/// Gets the errors.
		/// </summary>
		public void GetErrors()
		{
			SendMessage(new ErrorRequestMessageWrapper(++mTaskId));
		}

		/// <summary>
		/// Reset the buggy.
		/// </summary>
		public void Reset()
		{
			SendMessage(new ResetMessageWrapper(++mTaskId));
			mSender.Stop();
		}

		/// <summary>
		/// Gets a value indicating whether there is a connection with the buggy.
		/// </summary>
		public bool IsConnected { get; private set; }

		/// <summary>
		/// Occurs when [connected].
		/// </summary>
		public event EventHandler Connected;

		/// <summary>
		/// Occurs when [disconnected].
		/// </summary>
		public event EventHandler Disconnected;

		/// <summary>
		/// Occurs when (any) message is received.
		/// </summary>
		public event EventHandler<MessageReceivedEventArgs<BaseBuggyMessageWrapper>> MessageReceived;

		/// <summary>
		/// Occurs when [version message received].
		/// </summary>
		public event EventHandler<MessageReceivedEventArgs<VersionMessageWrapper>> VersionMessageReceived;

		/// <summary>
		/// Occurs when a message is send to the buggy.
		/// </summary>
		public event EventHandler<MessageSendEventArgs> MessageSend;

		/// <summary>
		/// Gets the error(s) the buggy encountered.
		/// </summary>
		/// <exception cref="System.NotImplementedException"></exception>
		public void GetError()
		{
			throw new NotImplementedException();
		}

		#endregion IBuggyCommunicationService
	}
}