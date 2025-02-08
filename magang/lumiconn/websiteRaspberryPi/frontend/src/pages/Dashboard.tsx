import React from 'react';
import Sidebar from '../components/Sidebar';
import { Outlet } from 'react-router-dom';

const Dashboard: React.FC = () => {
  return (
    <div className="flex bg-gradient-to-b from-gray-900 to-gray-950">
      <Sidebar />
      <main className="flex-grow">
        <Outlet />
      </main>
    </div>
  );
};

export default Dashboard;
