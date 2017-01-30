using System;
using PL.BuggySoft.Infrastructure.Models.Messages;

namespace PL.BuggySoft.Infrastructure.Services
{
	/// <summary>event arguments for when a message of type T has been received.
	/// </summary>
	/// <typeparam name="T">T</typeparam>
	/// <seealso cref="System.EventArgs" />
	public class MessageReceivedEventArgs<T> : EventArgs
		where T : BaseBuggyMessageWrapper
	{
		/// <summary>Initializes a new instance.
		/// </summary>
		/// <param name="message">The message.</param>
		public MessageReceivedEventArgs(T message)
		{
			Message = message;
		}

		/// <summary>The received message.
		/// </summary>
		public T Message { get; private set; }
	}

	/// <summary>Event arguments when a message is send to the buggy.
	/// </summary>
	public class MessageSendEventArgs : MessageReceivedEventArgs<BaseBuggyMessageWrapper>
	{
		/// <summary>Initializes a new instance of the <see cref="MessageSendEventArgs"/> class.
		/// </summary>
		/// <param name="message">The message.</param>
		public MessageSendEventArgs(BaseBuggyMessageWrapper message)
			: base(message)
		{
		}
	}

	/// <summary>Interface for a communication service with the buggy.
	/// </summary>
	public interface IBuggyCommunicationService
	{
		/// <summary>Start attempting to connect to the Buggy.</summary>
		void Connect(string ip, int port);

		/// <summary>Disconnect from the buggy.
		/// </summary>
		void Disconnect();

		/// <summary>Gets a value indicating whether there is a connection with the buggy.</summary>
		bool IsConnected { get; }

		/// <summary>Request the buggy to send its firmware version. Answer will be supplied via VersionMessageReceived event.
		/// </summary>
		void RequestVersion();

		/// <summary>Reset the buggy.
		/// </summary>
		void Reset();

		/// <summary>Requests the readout of the selected sensor(s).
		/// </summary>
		/// <param name="sensor">The sensor.</param>
		/// <param name="continues">if set to <c>true</c> [continues].</param>
		void RequestSensors(AnalogSensor sensor, bool continues = false);

		/// <summary>Steer the motors.
		/// </summary>
		/// <param name="left">The left speed and direction. Value between -100..100, negative is reverse.</param>
		/// <param name="right">The right speed and direction. Value between -100..100, negative is reverse.</param>
		void SteerMotor(sbyte left, sbyte right);

		/// <summary>Gets the error(s) the buggy encountered.
		/// </summary>
		void GetError();

		/// <summary>Occurs when [connected].
		/// </summary>
		event EventHandler Connected;

		/// <summary>Occurs when [disconnected].
		/// </summary>
		event EventHandler Disconnected;

		/// <summary>Occurs when (any) message is received.
		/// </summary>
		event EventHandler<MessageReceivedEventArgs<BaseBuggyMessageWrapper>> MessageReceived;

		/// <summary>Occurs when [version message received].
		/// </summary>
		event EventHandler<MessageReceivedEventArgs<VersionMessageWrapper>> VersionMessageReceived;

		/// <summary>Occurs when a message is send to the buggy.
		/// </summary>
		event EventHandler<MessageSendEventArgs> MessageSend;
	}
}