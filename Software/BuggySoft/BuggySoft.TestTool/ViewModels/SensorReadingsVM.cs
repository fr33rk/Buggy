using PL.BuggySoft.Infrastructure.Models.Messages;
using PL.Common.Prism;

namespace BuggySoft.TestTool.ViewModels
{
	public class SensorReadingsVM : ViewModelBase
	{
		public void Update(BaseBuggyMessageWrapper messageWrapper)
		{
			if (messageWrapper is SensorResultMessageWrapper)
			{
				Update((SensorResultMessageWrapper)messageWrapper);
			}
			else if (messageWrapper is SensorResultAllMessageWrapper)
			{
				Update((SensorResultAllMessageWrapper)messageWrapper);
			}
		}

		public void Update(SensorResultMessageWrapper sensorMessage)
		{
			// Test each time to prevent 'blinking'. E.g. when continues measuring the front setting the value first to null and then to
			// the actual value might causes the value to blink.
			DistanceLeft = sensorMessage.Sensor == AnalogSensor.DistanceLeft ? (ushort?)sensorMessage.Result : null;
			DistanceRight = sensorMessage.Sensor == AnalogSensor.DistanceRight ? (ushort?)sensorMessage.Result : null;
			DistanceFront = sensorMessage.Sensor == AnalogSensor.DistanceFront ? (ushort?)sensorMessage.Result : null;
			Light = sensorMessage.Sensor == AnalogSensor.Light ? (ushort?)sensorMessage.Result : null;
			Microphone = sensorMessage.Sensor == AnalogSensor.Microphone ? (ushort?)sensorMessage.Result : null;
			LineLeft = null;
			LineRight = null;
		}

		public void Update(SensorResultAllMessageWrapper sensorMessage)
		{
			DistanceLeft = sensorMessage.DistanceLeft;
			DistanceRight = sensorMessage.DistanceRight;
			DistanceFront = sensorMessage.DistanceFront;
			Light = sensorMessage.Light;
			Microphone = sensorMessage.Microphone;
			LineLeft = sensorMessage.LineSensorLeft;
			LineRight = sensorMessage.LineSensorRight;
		}

		public void Clear()
		{
			DistanceLeft = null;
			DistanceRight = null;
			DistanceFront = null;
			Microphone = null;
			Light = null;
			LineLeft = null;
			LineRight = null;
		}

		#region Property Distance Left

		private ushort? mDistanceLeft;

		public ushort? DistanceLeft
		{
			get { return mDistanceLeft; }
			private set
			{
				mDistanceLeft = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Property Distance Left

		#region Distance Right

		private ushort? mDistanceRight;

		public ushort? DistanceRight
		{
			get { return mDistanceRight; }
			private set
			{
				mDistanceRight = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Distance Right

		#region Distance Front

		private ushort? mDistanceFront;

		public ushort? DistanceFront
		{
			get { return mDistanceFront; }
			private set
			{
				mDistanceFront = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Distance Front

		#region Light

		private ushort? mLight;

		public ushort? Light
		{
			get { return mLight; }
			private set
			{
				mLight = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Light

		#region Microphone

		private ushort? mMicrophone;

		public ushort? Microphone
		{
			get { return mMicrophone; }
			private set
			{
				mMicrophone = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Microphone

		#region Line Left

		private bool? mLineLeft;

		public bool? LineLeft
		{
			get { return mLineLeft; }
			private set
			{
				mLineLeft = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Line Left

		#region Line Right

		private bool? mLineRight;

		public bool? LineRight
		{
			get { return mLineRight; }
			private set
			{
				mLineRight = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Line Right
	}
}