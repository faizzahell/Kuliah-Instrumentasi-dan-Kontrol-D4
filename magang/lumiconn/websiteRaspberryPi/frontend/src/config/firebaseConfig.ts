import { initializeApp } from 'firebase/app';
import { getAuth, GoogleAuthProvider } from 'firebase/auth';

const firebaseConfig = {
  apiKey: "AIzaSyB9fu2jST7v9YKTFHQoe2WhdrbfgmA3ueA",
  authDomain: "lumiconn-60b88.firebaseapp.com",
  projectId: "lumiconn-60b88",
  storageBucket: "lumiconn-60b88.firebasestorage.app",
  messagingSenderId: "17623276390",
  appId: "1:17623276390:web:37bd96363982e86c0106a7",
  measurementId: "G-VMGSD4MET5"
};

const app = initializeApp(firebaseConfig);
const auth = getAuth(app);

const googleProvider = new GoogleAuthProvider();

export { auth, googleProvider };
