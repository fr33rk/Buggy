namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper for the message to request error state of the buggy.
	/// </summary>
	/// <seealso cref="PL.BuggySoft.Infrastructure.Models.Messages.BaseBuggyMessageWrapper" />
	public class ErrorRequestMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>Initializes a new instance of the <see cref="ErrorRequestMessageWrapper"/> class.
		/// </summary>
		/// <param name="taskId">The task identifier.</param>
		public ErrorRequestMessageWrapper(ushort taskId)
			: base(BuggyCommand.SendError, true, taskId, 0)
		{
		}
	}
}