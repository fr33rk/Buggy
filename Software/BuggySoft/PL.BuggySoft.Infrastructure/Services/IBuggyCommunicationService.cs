using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL.BuggySoft.Infrastructure.Services
{
	public interface IBuggyCommunicationService
	{
		/// <summary>Start attempting to connect to the Buggy.</summary>
		void Connect();
	}

}
