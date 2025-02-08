import React from 'react';
import { Routes, Route, Navigate, useLocation } from 'react-router-dom';
import { useAuthState } from 'react-firebase-hooks/auth';
import { auth } from './config/firebaseConfig';
import { CSSTransition, TransitionGroup } from 'react-transition-group';

import Login from './pages/Login';
import Dashboard from './pages/Dashboard';
import Commuterline from './pages/Commuterline';
import Station from './pages/Station';
import Announcement from './pages/Announcement';
import Advertisment from './pages/Advertisment';
import Controlling from './pages/Controlling';
import Support from './pages/Support';
import Register from './pages/Register';
import DashboardContent from './components/DashboardContent';
import LocalTrain from './pages/LocalTrain';

const App: React.FC = () => {
  const [user] = useAuthState(auth);
  const location = useLocation();

  return (
    <TransitionGroup className="transition-group">
      <CSSTransition key={location.key} timeout={300} classNames="fade">
        <Routes location={location}>
          <Route path="/login" element={!user ? <Login /> : <Navigate to="/dashboard" />} />
          <Route path="/register" element={!user ? <Register /> : <Navigate to="/login" />} />
          <Route path="/dashboard" element={user ? <Dashboard /> : <Navigate to="/login" />}>
            <Route index element={<DashboardContent />} />
          </Route>
          <Route path="/commuterline" element={user ? <Commuterline /> : <Navigate to="/login" />} />
          <Route path="/localtrain" element={user ? <LocalTrain /> : <Navigate to="/login" />} />
          <Route path="/station" element={user ? <Station/> : <Navigate to="/login" />} />
          <Route path="/announcement" element={user ? <Announcement /> : <Navigate to="/login" />} />
          <Route path="/advertisment" element={user ? <Advertisment/> : <Navigate to="/login" />} />
          <Route path="/controlling" element={user ? <Controlling /> : <Navigate to="/login" />} />
          <Route path="/support" element={user ? <Support /> : <Navigate to="/login" />} />
          <Route path="*" element={<Navigate to={user ? "/dashboard" : "/login"} />} />
        </Routes>
      </CSSTransition>
    </TransitionGroup>
  );
};

export default App;
