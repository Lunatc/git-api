import './App.css';
import React, { useState, useEffect} from 'react';
import { Form, Card, Image, Icon} from 'semantic-ui-react'; 
function App() {
  const [name, setName] = useState('');
  const [userName, setUsername] = useState('');
  const [followers, setFollowers] = useState('');
  const [following, setFollowing] = useState('');
  const [repos, setRepos] = useState('');
  const [avatar, setAvatar] = useState('');
  const [userInput,setUserInput] = useState('');
  //const [error, setError] = useState(null);

  useEffect(() => {
    fetch("https://api.github.com/users/Lunatc")
    .then(res => res.json())
    .then(data => {
      setData(data);
    });
  }, []);

  const setData = ({name, login, followers, following, public_repos, avatar_url}) => {
    setName(name);
    setUsername(login);
    setFollowers(followers);
    setFollowing(following);
    setRepos(public_repos);
    setAvatar(avatar_url);
  }

  const handleSearch = (e) => {
    setUserInput(e.target.value)
  }

  const handleSubmit = () => {
    fetch(`https://api.github.com/users/${userInput}`)
    .then(res => res.json())
    .then(data => {
      setData(data);
    })
  }

  return (
    <div>
      <div className="navbar">Github Search</div>
      <div className="search">
        <Form onSubmit={handleSubmit}>
          <Form.Group>
            <Form.Input placeholder="Github user" name="github user" onChange={handleSearch}/>
            <Form.Button content="Search"/>        
          </Form.Group>
        </Form>
      </div>
      <div className="card">
        <Card>
          <Image src={avatar} wrapped ui={false}/>
          <Card.Content>
            <Card.Header>{name} - {userName}</Card.Header>
          </Card.Content>
          <Card.Content extra>
            <p>
              <Icon name='user'/>
              {followers} Followers
            </p>
          </Card.Content>
          <Card.Content extra>
            <p>
              <Icon name='user'/>
              {repos} Repos
            </p>
          </Card.Content>
          <Card.Content extra>
            <p>
              <Icon name='user'/>
              {following} Following
            </p>
          </Card.Content>
        </Card>

      </div>
    </div>
  );
}

export default App;
