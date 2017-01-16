using System.Diagnostics.CodeAnalysis;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper around the reset request message.
	///
	/// </summary>
	public class ResetMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>Initializes a new instance of the <see cref="ResetMessageWrapper"/> class.
		/// </summary>
		/// <param name="taskId">The task identifier.</param>
		[ExcludeFromCodeCoverage]
		public ResetMessageWrapper(ushort taskId)
			: base(BuggyCommand.Reset, false, taskId, 0)
		{
		}
	}
}