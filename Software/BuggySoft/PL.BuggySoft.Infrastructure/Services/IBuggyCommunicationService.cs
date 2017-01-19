using System;
using PL.BuggySoft.Infrastructure.Models.Messages;

namespace PL.BuggySoft.Infrastructure.Services
{
	public class MessageReceivedEventArgs<T> : EventArgs
		where T : BaseBuggyMessageWrapper
	{
		/// <summary>Initializes a new instance of the <see cref="MessageReceivedEventArgs"/> class.
		/// </summary>
		/// <param name="message">The message.</param>
		public MessageReceivedEventArgs(T message)
		{
			Message = message;
		}

		public T Message { get; private set; }
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
	}
}