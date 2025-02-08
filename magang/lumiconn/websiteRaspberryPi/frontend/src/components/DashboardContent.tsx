import React, {useState} from 'react';
import { MapContainer, TileLayer } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';
import { Pie } from 'react-chartjs-2';
import { Chart as ChartJS, ArcElement, Tooltip, Legend } from 'chart.js';
import { FaCog, FaSignal, FaBullhorn} from 'react-icons/fa';
import '../index.css'

ChartJS.register(ArcElement, Tooltip, Legend);

const DashboardContent: React.FC = () => {
  const [selectedOption, setSelectedOption] = useState('Commuterline');
  const center: [number, number] = [-6.2, 106.87];

  const commuterlineData = {
    chartData: {
      labels: ['Commuterline Online', 'Commuterline Offline'],
      datasets: [
        {
          data: [12, 3],
          backgroundColor: ['#117554', '#D91656'],
          hoverBackgroundColor: ['#399918', '#F5004F'],
        },
      ],
    },
    adData: {
      labels: ['Advertisement Play', 'Ads Not Playing'],
      datasets: [
        {
          data: [25, 30],
          backgroundColor: ['#6420AA', '#FB8B24'],
          hoverBackgroundColor: ['#7E30E1', '#FF9843'],
        },
      ],
    },
    maintenanceData: {
      labels: ['Healthy Commuterline', 'Maintenance Needed'],
      datasets: [
        {
          data: [95, 5],
          backgroundColor: ['#117554', '#FB8B24'],
          hoverBackgroundColor: ['#399918', '#FF9843'],
        },
      ],
    },
  };

  const localTrainData = {
    chartData: {
      labels: ['Local Train Online', 'Local Train Offline'],
      datasets: [
        {
          data: [8, 7],
          backgroundColor: ['#0077B6', '#FF6F61'],
          hoverBackgroundColor: ['#0096C7', '#FF8A80'],
        },
      ],
    },
    adData: {
      labels: ['Advertisement Play', 'Ads Not Playing'],
      datasets: [
        {
          data: [15, 40],
          backgroundColor: ['#D2691E', '#FFD700'],
          hoverBackgroundColor: ['#DE8C5A', '#FFEC4A'],
        },
      ],
    },
    maintenanceData: {
      labels: ['Healthy Local Train', 'Maintenance Needed'],
      datasets: [
        {
          data: [85, 15],
          backgroundColor: ['#6A5ACD', '#FFA500'],
          hoverBackgroundColor: ['#7A6CC7', '#FFB732'],
        },
      ],
    },
  };

  const selectedData = selectedOption === 'Commuterline' ? commuterlineData : localTrainData;

  return (
    <div className="relative h-screen">
      <div className="flex justify-between bg-gradient-to-r from-gray-900 to-gray-950 text-white m-3 p-4 rounded-lg absolute top-0 left-0 right-0 z-10">
        <div className="flex flex-col items-center gap-2">
          <div className='flex gap-2'>
            <FaSignal className="text-green-400 text-2xl" />
            <h3 className="text-lg font-semibold">{selectedOption} Online</h3>
          </div>
          <div className="bg-gray-800 w-full h-full p-3 flex justify-center items-center rounded-xl">
            <p className="text-2xl font-bold">{selectedData.chartData.datasets[0].data[0]}</p>
          </div>
        </div>

        <div className="flex flex-col items-center gap-2">
          <div className='flex gap-2'>
            <FaSignal className="text-red-600 text-2xl" />
            <h3 className="text-lg font-semibold">{selectedOption} Offline</h3>
          </div>
          <div className="bg-gray-800 w-full h-full p-3 flex justify-center items-center rounded-xl">
            <p className="text-2xl font-bold">{selectedData.chartData.datasets[0].data[1]}</p>
          </div>
        </div>

        <div className="flex flex-col items-center gap-2">
          <div className='flex gap-2'>
            <FaBullhorn className="text-green-400 text-2xl" />
            <h3 className="text-lg font-semibold">Playing Ads Today</h3>
          </div>
          <div className="bg-gray-800 w-full h-full p-3 flex justify-center items-center rounded-xl">
            <p className="text-2xl font-bold">{selectedData.adData.datasets[0].data[0]}</p>
          </div>
        </div>

        <div className="flex flex-col items-center gap-2">
          <div className='flex gap-2'>
            <FaBullhorn className="text-red-600 text-2xl" />
            <h3 className="text-lg font-semibold">Not Playing Ads Today</h3>
          </div>
          <div className="bg-gray-800 w-full h-full p-3 flex justify-center items-center rounded-xl">
            <p className="text-2xl font-bold">{selectedData.adData.datasets[0].data[1]}</p>
          </div>
        </div>

        <div className="flex flex-col items-center gap-2">
          <div className='flex gap-2'>
            <FaCog className="text-yellow-300 text-2xl" />
            <h3 className="text-lg font-semibold">Warning Maintenance</h3>
          </div>
          <div className="bg-gray-800 w-full h-full p-3 flex justify-center items-center rounded-xl">
            <p className="text-2xl font-bold">{selectedData.maintenanceData.datasets[0].data[1]}</p>
          </div>
        </div>
      </div>

      <div className="flex justify-between bg-gradient-to-b from-gray-900 to-gray-950 text-white m-3 mb-10 p-4 rounded-lg absolute bottom-0 right-0 z-10">
        <div className="flex flex-col items-center gap-2 h-full">
          <div className="flex gap-2 rounded-lg bg-gray-800 p-2">
            <div className={`p-2 rounded-lg ${selectedOption === 'Commuterline' ? 'bg-yellow-400' : 'bg-gray-700'}`}
              onClick={() => setSelectedOption('Commuterline')}
            >
              <h3>Commuterline</h3>
            </div>
            <div className={`p-2 rounded-lg ${selectedOption === 'Local Train' ? 'bg-yellow-400' : 'bg-gray-700'}`}
              onClick={() => setSelectedOption('Local Train')}
            >
              <h3>Local Train</h3>
            </div>
          </div>
          <div className="p-4 rounded-lg shadow-md">
            <Pie 
              className='h-24' 
              data={selectedData.chartData} 
              options={{
                plugins: {
                  legend: {
                    align: 'start',
                    labels: {
                      color: 'white',
                    },
                  },
                },
              }}
            />
          </div>
          <div className="p-4 rounded-lg shadow-md">
            <Pie 
              className='h-24' 
              data={selectedData.adData} 
              options={{
                plugins: {
                  legend: {
                    align: 'start',
                    labels: {
                      color: 'white',
                    },
                  },
                },
              }}
            />
          </div>
          <div className="p-4 rounded-lg shadow-md">
            <Pie 
              className='h-24' 
              data={selectedData.maintenanceData} 
              options={{
                plugins: {
                  legend: {
                    align: 'start',
                    labels: {
                      color: 'white',
                    },
                  },
                },
              }}
            />
          </div>
        </div>
      </div>

      <div className="absolute top-0 bottom-0 left-0 right-0 z-0">
        <MapContainer
          center={center}
          zoom={12}
          style={{ width: '100%', height: '100%' }}
        >
          <TileLayer
            url="https://tile.thunderforest.com/transport-dark/{z}/{x}/{y}.png?apikey=78b0cd7efc0b438eb7cbb4d8e552bf76"
            className='map-tiles'                                   
          />
        </MapContainer>
      </div>
    </div>
  );
};

export default DashboardContent;
