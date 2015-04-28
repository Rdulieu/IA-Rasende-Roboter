%--------------------------------------------------------------------
%====================================================================
%
% Module consisting in:
%  - extracting the relevant information from a stimulus and
%  - thinking about the correct move to perform by the miner.
%
% Version: 	1.0
% Date:		2011/10
%
% Author(s):
%  1- Fabrice Lauri
%
% Status:
%  1- Associate Professor at the "Université de Technologie de
%     Belfort-Montbéliard", France
%     Laboratoire "Systèmes et Transports"
%
%====================================================================
%--------------------------------------------------------------------


:- use_module( decision ).


% ***************************************************************************************
%   Description of a stimulus in Rasende Roboter
% ***************************************************************************************
% 
%   Vector of 64-bit floats. Casting in integers is mandatory...
% 
%   Content:
%   - Id of the bottom left panel
%   - Id of the bottom right panel
%   - Id of the top left panel
%   - Id of the top right panel
%   - TargetId
%   - Positions (x,y) of the robots (x4)
% 
% ***************************************************************************************


startThinking( X ) :-
	init( X ).


think( Stimulus, Action ) :-
	Stimulus=[External_Stimulus | _],
	convertF2I( External_Stimulus, L ),
	move( L, Action ).


convertF2I( [], [] ).
convertF2I( [X | R1], [I | I1] ) :-
	I is integer( X ),
	convertF2I( R1, I1 ).
