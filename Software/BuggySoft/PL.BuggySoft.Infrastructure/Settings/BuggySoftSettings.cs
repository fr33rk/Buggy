using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL.BuggySoft.Infrastructure.Settings
{
	public class BuggySoftSettings
	{
		[DefaultValue("192.168.5.21")]
		public string IpAddress { get; set; } 

		[DefaultValue(6060)]
		public int IpPort { get; set; }
	}
}
