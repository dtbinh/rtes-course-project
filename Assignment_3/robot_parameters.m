% Number of links of the manipulator is always 6
NoOfLinks = 6;


% Define the DH parameters in "standard" (non-Craig) form
Link1 = [pi/2, 0, pi/2, 0];
Link2 = [0, 0.404, pi/2, 0];
Link3 = [-pi/2, 0, 0, 0];
Link4 = [pi/2, 0.025, 0, 0.405];
Link5 = [pi/2, 0, pi/2, 0];
Link6 = [0, 0, pi/2, 0];


% The following portion is required for the conformance testing of Modelrob
% library with respect to Robotics Toolbox
% Robotics Toolbox should be installed and should be in the path

link1 = Link([pi/2, 0, pi/2, 0], 'standard');
link2 = Link([0, 0.404, pi/2, 0], 'standard');
link3 = Link([-pi/2, 0, 0, 0], 'standard');
link4 = Link([pi/2, 0.025, 0, 0.405], 'standard');
link5 = Link([pi/2, 0, pi/2, 0], 'standard');
link6 = Link([0, 0, pi/2, 0], 'standard');

rob = robot({link1, link2, link3, link4, link5, link6});
rob.name = 'robot';


    
