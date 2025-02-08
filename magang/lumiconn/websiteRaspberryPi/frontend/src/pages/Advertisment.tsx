import React from 'react';
import Sidebar from '../components/Sidebar';

const Advertisment: React.FC = () => {
  return (
    <div className="flex bg-gradient-to-b from-gray-800 to-gray-900">
      <Sidebar />
      <main className="flex-grow p-6">
        <div className="w-full h-full flex justify-center items-center">
          <h1 className="text-white">Advertisment</h1>
        </div>
      </main>
    </div>
  );
};

export default Advertisment;