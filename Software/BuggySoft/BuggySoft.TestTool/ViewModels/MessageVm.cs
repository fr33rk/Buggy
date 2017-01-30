using System;
using System.Linq;
using PL.BuggySoft.Infrastructure.Models;
using PL.BuggySoft.Infrastructure.Models.Messages;

namespace BuggySoft.TestTool.ViewModels
{
	/// <summary>View model wrapper around a buggy message.
	/// </summary>
	public class MessageVm
	{
		#region Definitions

		private readonly BaseBuggyMessageWrapper mWrappedMessage;
		private readonly bool mWasReceived;

		#endregion Definitions

		#region Constructor(s)

		/// <summary>Initializes a new instance of the <see cref="MessageVm"/> class.
		/// </summary>
		/// <param name="wasReceived">if set to <c>true</c> [was receieved].</param>
		/// <param name="wrappedMessage">The wrapped message.</param>
		public MessageVm(bool wasReceived, BaseBuggyMessageWrapper wrappedMessage)
		{
			mWrappedMessage = wrappedMessage;
			mWasReceived = wasReceived;
		}

		#endregion Constructor(s)

		#region Properties

		/// <summary>Gets the direction indicator.
		/// </summary>
		public string Direction => mWasReceived ? "<" : ">";

		/// <summary>Gets the command.
		/// </summary>
		public BuggyCommand Command => mWrappedMessage.Command;

		/// <summary>Yes, when RTR, false otherwise.
		/// </summary>
		public string Rtr => mWrappedMessage.IsRtr ? "Yes" : "No";

		/// <summary>Gets the task identifier.
		/// </summary>
		public int TaskId => mWrappedMessage.TaskId;

		/// <summary>Yes. when in error, false otherwise.
		/// </summary>
		public string Error => mWrappedMessage.IsError ? "Yes" : "No";

		/// <summary>Gets the size of the data.
		/// </summary>
		public int DataSize => mWrappedMessage.DataSize;

		/// <summary>Gets the data.
		/// </summary>
		public string Data
		{
			get
			{
				var hexData = Array.ConvertAll(mWrappedMessage.Data.Take(DataSize).ToArray(), input => input.ToString("X2")).ToArray();
				return string.Join(" ", hexData);
			}
		}

		/// <summary>Gets the human readable data segment.
		/// </summary>
		public string DataInterpretation => mWrappedMessage.SpecificDataString();

		#endregion Properties
	}
}