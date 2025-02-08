import React, { useEffect, useState } from 'react';
import { FaHome, FaTrain, FaClipboard, FaBullhorn, FaAd, FaTools, FaHandsHelping, FaAngleLeft } from 'react-icons/fa';
import { NavLink } from 'react-router-dom';
import { auth } from '../config/firebaseConfig';
import { onAuthStateChanged, User } from 'firebase/auth';

const Sidebar: React.FC = () => {
  const [user, setUser] = useState<User | null>(null);
  const [profilePic, setProfilePic] = useState<string>('/images/defaultUser.png');
  const [isMinimized, setIsMinimized] = useState<boolean>(false);

  useEffect(() => {
    const unsubscribe = onAuthStateChanged(auth, (currentUser) => {
      if (currentUser) {
        setUser(currentUser);
        const userPhotoURL = currentUser.photoURL || '/images/defaultUser.png';
        setProfilePic(userPhotoURL);
      } else {
        setUser(null);
      }
    });

    return () => unsubscribe();
  }, []);

  const truncateText = (text: string, maxLength: number) => {
    if (text.length > maxLength) {
      return text.substring(0, maxLength) + "..";
    }
    return text;
  };

  const toggleSidebar = () => {
    setIsMinimized(!isMinimized);
  };

  return (
    <div
      className={`h-screen ${isMinimized ? 'w-20' : 'w-72'} bg-gradient-to-b from-gray-900 to-gray-950 text-white flex flex-col shadow-lg transition-all duration-300`}
    >
      <div className={`flex ${isMinimized ? 'justify-center' : 'justify-between'} items-center p-4`}>
        <img
          src={'/images/logo-lumiconn.svg'}
          alt="Profile"
          className={`w-48 h-12 rounded-full mr-3 tracking-wide ${isMinimized ? 'hidden' : 'block'}`}
        />
        <button
          className="text-white p-2 rounded-full hover:bg-yellow-400"
          onClick={toggleSidebar}
        >
          <FaAngleLeft className={`${isMinimized ? 'rotate-180' : ''} transition-all duration-500`} />
        </button>
      </div>

      {user && (
        <div className="flex items-center p-4 bg-gradient-to-r from-gray-950 to-gray-900 mb-2">
          <img
            src={profilePic}
            alt="Profile"
            className="w-12 h-12 rounded-full mr-3"
            onError={() => setProfilePic('/images/defaultUser.png')}
          />
          {!isMinimized && (
            <div>
              <p className="font-semibold`">{truncateText(user.displayName || "", 28)}</p>
              <p className="text-sm">{truncateText(user.email || "", 28)}</p>
            </div>
          )}
        </div>
      )}

      <hr className="border-t border-white my-4 mx-4" />

      <nav className="flex flex-col flex-grow px-4">
      <NavLink
        to="/"
        className={`flex items-center ${isMinimized ? 'p-3 items-center justify-center rounded-full' : "p-4 rounded-lg"} mb-2 hover:bg-yellow-400 hover:shadow-lg transition-all duration-300`}
      >
        <FaHome className={`${isMinimized ? 'text-xl' : "text-xl mr-3"}`} />
        <span className={`${isMinimized ? 'hidden' : 'font-semibold'}`}>Dashboard</span>
      </NavLink>

      <NavLink
        to="/commuterline"
        className={`flex items-center ${isMinimized ? 'p-3 items-center justify-center rounded-full' : "p-4 rounded-lg"} mb-2 hover:bg-yellow-400 hover:shadow-lg transition-all duration-300`}
      >
        <FaTrain className={`${isMinimized ? 'text-xl' : "text-xl mr-3"}`} />
        <span className={`${isMinimized ? 'hidden' : 'font-semibold'}`}>Commuterline</span>
      </NavLink>

      <NavLink
        to="/localtrain"
        className={`flex items-center ${isMinimized ? 'p-3 items-center justify-center rounded-full' : "p-4 rounded-lg"} mb-2 hover:bg-yellow-400 hover:shadow-lg transition-all duration-300`}
      >
        <FaTrain className={`${isMinimized ? 'text-xl' : "text-xl mr-3"}`} />
        <span className={`${isMinimized ? 'hidden' : 'font-semibold'}`}>Local Train</span>
      </NavLink>

      <NavLink
        to="/station"
        className={`flex items-center ${isMinimized ? 'p-3 items-center justify-center rounded-full' : "p-4 rounded-lg"} mb-2 hover:bg-yellow-400 hover:shadow-lg transition-all duration-300`}
      >
        <FaClipboard className={`${isMinimized ? 'text-xl' : "text-xl mr-3"}`} />
        <span className={`${isMinimized ? 'hidden' : 'font-semibold'}`}>Train Station</span>
      </NavLink>

      <NavLink
        to="/announcement"
        className={`flex items-center ${isMinimized ? 'p-3 items-center justify-center rounded-full' : "p-4 rounded-lg"} mb-2 hover:bg-yellow-400 hover:shadow-lg transition-all duration-300`}
      >
        <FaBullhorn className={`${isMinimized ? 'text-xl' : "text-xl mr-3"}`} />
        <span className={`${isMinimized ? 'hidden' : 'font-semibold'}`}>Announcement</span>
      </NavLink>

      <NavLink
        to="/advertisment"
        className={`flex items-center ${isMinimized ? 'p-3 items-center justify-center rounded-full' : "p-4 rounded-lg"} mb-2 hover:bg-yellow-400 hover:shadow-lg transition-all duration-300`}
      >
        <FaAd className={`${isMinimized ? 'text-xl' : "text-xl mr-3"}`} />
        <span className={`${isMinimized ? 'hidden' : 'font-semibold'}`}>Advertisment</span>
      </NavLink>

      <NavLink
        to="/controlling"
        className={`flex items-center ${isMinimized ? 'p-3 items-center justify-center rounded-full' : "p-4 rounded-lg"} mb-2 hover:bg-yellow-400 hover:shadow-lg transition-all duration-300`}
      >
        <FaTools className={`${isMinimized ? 'text-xl' : "text-xl mr-3"}`} />
        <span className={`${isMinimized ? 'hidden' : 'font-semibold'}`}>Controlling</span>
      </NavLink>

      <NavLink
        to="/support"
        className={`flex items-center ${isMinimized ? 'p-3 items-center justify-center rounded-full' : "p-4 rounded-lg"} mb-2 hover:bg-yellow-400 hover:shadow-lg transition-all duration-300`}
      >
        <FaHandsHelping className={`${isMinimized ? 'text-xl' : "text-xl mr-3"}`} />
        <span className={`${isMinimized ? 'hidden' : 'font-semibold'}`}>Support</span>
      </NavLink>
      </nav>
    </div>
  );
};

export default Sidebar;
