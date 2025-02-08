import React, { useState } from 'react';
import { signInWithEmailAndPassword, signInWithPopup } from 'firebase/auth';
import { auth, googleProvider } from '../config/firebaseConfig';
import { useNavigate } from 'react-router-dom';
import { FaGoogle } from 'react-icons/fa';

const Login: React.FC = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState('');
  const navigate = useNavigate();

  const handleGoogleLogin = async () => {
    try {
      const result = await signInWithPopup(auth, googleProvider);
      console.log('Google login success:', result.user);
      navigate('/dashboard');
    } catch (error) {
      console.error('Google login error:', error);
      setError('Google login failed');
    }
  };

  const handleLogin = async (e: React.FormEvent) => {
    e.preventDefault();
    setError('');
  
    try {
      await signInWithEmailAndPassword(auth, email, password);
      navigate('/dashboard');
    } catch (error: unknown) {
      if (error instanceof Error) {
        if (error.message.includes('wrong-password')) {
          setError('Invalid password');
        } else if (error.message.includes('user-not-found')) {
          setError('No account found with this email');
        } else {
          setError('Login failed. Please try again.');
        }
        console.error('Login error:', error.message);
      } else {
        setError('An unknown error occurred.');
      }
    }
  };

  return (
    <div className="flex items-center justify-center h-screen bg-gray-900 text-white">
      <div className="bg-gray-800 p-8 rounded-xl shadow-lg w-96 max-w-sm">
        <div className='w-full flex justify-center items-center mb-6'>
          <img
            src={'/images/logo-ugm.png'}
            alt="Profile"
            className="w-14 h-14 rounded-full mr-3"
          />
          <img
            src={'/images/logo-lumiconn.svg'}
            alt="Profile"
            className="w-48 h-24 rounded-full mr-3"
          />
        </div>
        <h2 className="text-3xl font-semibold text-center mb-10 text-white font-sans">COMMUTERLINE <span className="text-yellow-400 font-serif">Monitoring</span></h2>
        
        {error && <p className="text-red-400 text-center mb-4">{error}</p>}
        
        <form onSubmit={handleLogin} className="space-y-6">
          <input
            type="email"
            placeholder="Email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            className="w-full p-3 bg-gray-700 border border-gray-600 rounded-lg focus:outline-none focus:ring-2 focus:ring-yellow-400 text-white"
            required
          />
          
          <input
            type="password"
            placeholder="Password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            className="w-full p-3 bg-gray-700 border border-gray-600 rounded-lg focus:outline-none focus:ring-2 focus:ring-yellow-400 text-white"
            required
          />
          
          <button
            type="submit"
            className="w-full p-3 bg-yellow-400 text-white font-bold rounded-lg hover:bg-amber-500 focus:outline-none focus:ring-2 focus:ring-blue-400 transition"
          >
            Login
          </button>
        </form>

        <div className="mt-6 text-center">
          <p className="text-sm text-gray-400 mb-4">Or</p>
          <button
            className="w-full p-3 bg-amber-600 text-white rounded-lg hover:bg-yellow-500 focus:outline-none focus:ring-2 focus:ring-blue-400 transition flex items-center justify-center"
            onClick={handleGoogleLogin}
          >
            <FaGoogle className="mr-3 text-white text-xl" />
            Login with Google
          </button>
        </div>

        <div className="mt-6 text-center">
          <p className="text-sm text-gray-400">No account? <a href="/register" className="text-amber-400 hover:text-yellow-400">Register now</a></p>
        </div>
      </div>
    </div>
  );
};

export default Login;
