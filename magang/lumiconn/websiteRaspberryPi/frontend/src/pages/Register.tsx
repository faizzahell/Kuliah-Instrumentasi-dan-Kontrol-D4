import React, { useState } from 'react';
import { createUserWithEmailAndPassword } from 'firebase/auth';
import { auth } from '../config/firebaseConfig';
import { useNavigate } from 'react-router-dom';

const Register: React.FC = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');
  const [error, setError] = useState('');
  const navigate = useNavigate();

  const handleRegister = async (e: React.FormEvent) => {
    e.preventDefault();
    setError('');

    if (password !== confirmPassword) {
      setError('Passwords do not match');
      return;
    }

    try {
      await createUserWithEmailAndPassword(auth, email, password);
      navigate('/dashboard');
    } catch (error: unknown) {
      if (error instanceof Error) {
        setError(error.message);
        console.error('Registration error:', error.message);
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
        
        <form onSubmit={handleRegister} className="space-y-6">
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
          
          <input
            type="password"
            placeholder="Confirm Password"
            value={confirmPassword}
            onChange={(e) => setConfirmPassword(e.target.value)}
            className="w-full p-3 bg-gray-700 border border-gray-600 rounded-lg focus:outline-none focus:ring-2 focus:ring-yellow-400 text-white"
            required
          />
          
          <button
            type="submit"
            className="w-full p-3 bg-yellow-400 text-white font-bold rounded-lg hover:bg-amber-500 focus:outline-none focus:ring-2 focus:ring-blue-400 transition"
          >
            Register
          </button>
        </form>

        <div className="mt-6 text-center">
          <p className="text-sm text-gray-400">Already have an account? <a href="/login" className="text-amber-400 hover:text-yellow-400">Login now</a></p>
        </div>
      </div>
    </div>
  );
};

export default Register;
