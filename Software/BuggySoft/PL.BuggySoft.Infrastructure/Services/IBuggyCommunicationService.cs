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

	public class MessageSendEventArgs : MessageReceivedEventArgs<BaseBuggyMessageWrapper>
	{
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

		/// <summary>Request the buggy to send its firmware version. Answer will be supplied via VersionMessageReceived event.
		/// </summary>
		void RequestVersion();

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

		event EventHandler<MessageSendEventArgs> MessageSend;
	}
}